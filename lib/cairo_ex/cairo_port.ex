defmodule CairoEx.CairoPort do
  @moduledoc false

  @type t :: GenServer.t()

  @packet_log_message 0x10
  @packet_cmd_result 0x20

  use GenServer

  require Logger

  def start_link(args \\ []) do
    GenServer.start_link(__MODULE__, args)
  end

  @impl true
  def init(_) do
    port =
      Port.open({:spawn_executable, exe()}, [
        :use_stdio,
        :binary,
        :exit_status,
        {:packet, 2}
      ])

    {:ok, %{port: port}}
  end

  def command(port, cmd) do
    port
    |> GenServer.call({:command, cmd})
    |> handle_command_result()
  end

  defp handle_command_result({:error, :cx_invalid_reference}) do
    raise CairoEx.Error, message: "Invalid reference"
  end

  defp handle_command_result({:error, :cx_unknown_cmd}) do
    raise CairoEx.Error, message: "Unknown command"
  end

  defp handle_command_result({:error, :cx_decode}) do
    raise CairoEx.Error, message: "Command decoding error"
  end

  defp handle_command_result({:error, :cx_encode}) do
    raise CairoEx.Error, message: "Command encoding error"
  end

  defp handle_command_result(result) do
    result
  end

  @impl true
  def handle_call({:command, cmd}, _from, state) do
    packet = :erlang.term_to_binary(cmd)

    Port.command(state.port, packet)

    result =
      receive do
        {_, {:data, <<@packet_cmd_result, response::binary>>}} ->
          :erlang.binary_to_term(response)
      after
        5000 -> {:error, :port_timeout}
      end

    {:reply, result, state}
  end

  @impl true
  def handle_info(
        {port, {:data, <<@packet_log_message, level_num, message::binary>>}},
        %{port: port} = state
      ) do
    Logger.log(level(level_num), ["CairoEx.CairoPort: ", message])
    {:noreply, state}
  end

  defp exe() do
    Application.app_dir(:cairo_ex, ["priv", "cairo_ex"])
  end

  defp level(0), do: :error
  defp level(1), do: :warn
  defp level(2), do: :debug
end

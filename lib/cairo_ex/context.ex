defmodule CairoEx.Context do
  @moduledoc """
  Cairo Context
  """

  @type t :: %__MODULE__{}

  alias CairoEx.{
    CairoPort,
    Surface
  }

  defstruct [:handle, :port]

  @spec create(
          cairo :: CairoEx.t(),
          surface :: Surface.t()
        ) ::
          {:ok, t()} | {:error, CairoEx.error_reason()}
  def create(cairo, %Surface{} = surface) do
    cmd = {:create, [surface.handle]}

    cairo
    |> CairoPort.command(cmd)
    |> case do
      {:ok, handle} ->
        {:ok, %__MODULE__{
          port: cairo,
          handle: handle
        }}

      error ->
        error
    end
  end

  @spec set_source_rgb(context :: t(), r :: float(), g :: float(), b :: float()) :: t()
  def set_source_rgb(%__MODULE__{} = context, r, g, b) do
    command(context, {:set_source_rgb, [context.handle, r, g, b]})
  end

  @spec paint(context :: t()) :: t()
  def paint(%__MODULE__{} = context) do
    command(context, {:paint, [context.handle]})
  end

  @spec line_to(context :: t(), x :: float(), y :: float()) :: t()
  def line_to(%__MODULE__{} = context, x, y) do
    command(context, {:line_to, [context.handle, x, y]})
  end

  @spec move_to(context :: t(), x :: float(), y :: float()) :: t()
  def move_to(%__MODULE__{} = context, x, y) do
    command(context, {:move_to, [context.handle, x, y]})
  end

  @spec set_line_width(context :: t(), width :: float()) :: t()
  def set_line_width(%__MODULE__{} = context, width) do
    command(context, {:set_line_width, [context.handle, width]})
  end

  @spec stroke(context :: t()) :: t()
  def stroke(%__MODULE__{} = context) do
    command(context, {:stroke, [context.handle]})
  end

  defp command(%__MODULE__{port: port} = context, cmd) do
    case CairoPort.command(port, cmd) do
      :ok -> context
      other -> other
    end
  end
end

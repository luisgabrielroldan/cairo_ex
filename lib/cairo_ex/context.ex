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
        {:ok, %__MODULE__{port: cairo, handle: handle}}

      error ->
        error
    end
  end

  @spec set_source_rgb(context :: t(), r :: float(), g :: float(), b :: float()) :: :ok | {:error, CairoEx.error_reason()}
  def set_source_rgb(%__MODULE__{} = context, r, g, b) do
    CairoPort.command(context.port, {:set_source_rgb, [context.handle, r, g, b]})
  end

  @spec paint(context :: t()) :: :ok | {:error, CairoEx.error_reason()}
  def paint(%__MODULE__{} = context) do
    CairoPort.command(context.port, {:paint, [context.handle]})
  end

  @spec line_to(context :: t(), x :: float(), y :: float()) :: :ok | {:error, CairoEx.error_reason()}
  def line_to(%__MODULE__{} = context, x, y) do
    CairoPort.command(context.port, {:line_to, [context.handle, x, y]})
  end

  @spec move_to(context :: t(), x :: float(), y :: float()) :: :ok | {:error, CairoEx.error_reason()}
  def move_to(%__MODULE__{} = context, x, y) do
    CairoPort.command(context.port, {:move_to, [context.handle, x, y]})
  end

  @spec set_line_width(context :: t(), width :: float()) :: :ok | {:error, CairoEx.error_reason()}
  def set_line_width(%__MODULE__{} = context, width) do
    CairoPort.command(context.port, {:set_line_width, [context.handle, width]})
  end

  @spec stroke(context :: t()) :: :ok | {:error, CairoEx.error_reason()}
  def stroke(%__MODULE__{} = context) do
    CairoPort.command(context.port, {:stroke, [context.handle]})
  end
end

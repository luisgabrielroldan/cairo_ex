defmodule CairoEx.Surface do
  @moduledoc """
  Cairo Surface
  """

  @type t :: %__MODULE__{}

  alias CairoEx.CairoPort

  defstruct [:handle, :port]

  @spec image_surface_create(
          cairo :: CairoEx.t(),
          format :: CairoEx.format(),
          width :: integer(),
          height :: integer()
        ) ::
          {:ok, t()} | {:error, CairoEx.error_reason()}
  def image_surface_create(cairo, format, width, height) do
    cmd = {:image_surface_create, [format, width, height]}

    cairo
    |> CairoPort.command(cmd)
    |> case do
      {:ok, handle} ->
        {:ok, %__MODULE__{port: cairo, handle: handle}}

      error ->
        error
    end
  end

  @spec write_to_png(surface :: t(), String.t()) :: :ok | {:error, CairoEx.error_reason()}
  def write_to_png(%__MODULE__{} = surface, filename) when is_binary(filename) do
    CairoPort.command(surface.port, {:surface_write_to_png, [surface.handle, filename]})
  end

  @spec destroy(surface :: t()) :: :ok | {:error, CairoEx.error_reason()}
  def destroy(%__MODULE__{} = surface) do
    CairoPort.command(surface.port, {:surface_destroy, [surface.handle]})
  end

end

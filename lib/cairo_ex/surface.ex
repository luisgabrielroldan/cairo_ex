defmodule CairoEx.Surface do
  @moduledoc """
  Cairo Surface
  """

  alias CairoEx.{CairoPort, Ref}

  @spec image_surface_create(
          cairo :: CairoEx.t(),
          format :: CairoEx.format(),
          width :: integer(),
          height :: integer()
        ) ::
          {:ok, Ref.t()} | {:error, CairoEx.error_reason()}
  def image_surface_create(cairo, format, width, height) do
    cmd = {:image_surface_create, [format, width, height]}

    cairo
    |> CairoPort.command(cmd)
    |> case do
      {:ok, handle} ->
        {:ok, Ref.make(handle, :surface, cairo)}

      error ->
        error
    end
  end

  @spec write_to_png(surface :: Ref.t(), String.t()) :: :ok | {:error, CairoEx.error_reason()}
  def write_to_png(%Ref{type: :surface} = surface, filename) when is_binary(filename) do
    CairoPort.command(surface.port, {:surface_write_to_png, [surface.handle, filename]})
  end

  @spec destroy(surface :: Ref.t()) :: :ok | {:error, CairoEx.error_reason()}
  def destroy(%Ref{type: :surface} = surface) do
    CairoPort.command(surface.port, {:surface_destroy, [surface.handle]})
  end
end

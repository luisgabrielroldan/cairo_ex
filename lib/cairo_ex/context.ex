defmodule CairoEx.Context do
  @moduledoc """
  Cairo Context
  """

  alias CairoEx.{
    CairoPort,
    Matrix,
    Ref
  }

  @spec create(surface :: Ref.t()) ::
          {:ok, Ref.t()} | {:error, CairoEx.error_reason()}
  def create(%Ref{type: :surface} = surface) do
    port = surface.port
    cmd = {:create, [surface.handle]}

    port
    |> CairoPort.command(cmd)
    |> case do
      {:ok, handle} ->
        {:ok, Ref.make(handle, :context, port)}

      error ->
        error
    end
  end

  @spec get_target(context :: Ref.t()) ::
          {:ok, Ref.t()} | {:error, CairoEx.error_reason()}
  def get_target(%Ref{type: :context} = context) do
    port = context.port
    cmd = {:get_target, [context.handle]}

    port
    |> CairoPort.command(cmd)
    |> case do
      {:ok, handle} ->
        {:ok, Ref.make(handle, :surface, port)}

      error ->
        error
    end
  end

  @spec user_to_device(context :: Ref.t(), x :: float(), y :: float()) ::
          {:ok, CairoEx.vector()} | {:error, CairoEx.error_reason()}
  def user_to_device(%Ref{} = context, x, y) do
    context.port
    |> CairoPort.command({:user_to_device, [context.handle, x / 1, y / 1]})
    |> case do
      {:ok, [x1, y1]} -> {:ok, {x1, y1}}
      error -> error
    end
  end

  @spec user_to_device_distance(context :: Ref.t(), dx :: float(), dy :: float()) ::
          {:ok, CairoEx.vector()} | {:error, CairoEx.error_reason()}
  def user_to_device_distance(%Ref{} = context, dx, dy) do
    context.port
    |> CairoPort.command({:user_to_device_distance, [context.handle, dx / 1, dy / 1]})
    |> case do
      {:ok, [dx1, dy1]} -> {:ok, {dx1, dy1}}
      error -> error
    end
  end

  @spec device_to_user(context :: Ref.t(), x :: float(), y :: float()) ::
          {:ok, CairoEx.vector()} | {:error, CairoEx.error_reason()}
  def device_to_user(%Ref{} = context, x, y) do
    context.port
    |> CairoPort.command({:device_to_user, [context.handle, x / 1, y / 1]})
    |> case do
      {:ok, [x1, y1]} -> {:ok, {x1, y1}}
      error -> error
    end
  end

  @spec device_to_user_distance(context :: Ref.t(), dx :: float(), dy :: float()) ::
          {:ok, CairoEx.vector()} | {:error, CairoEx.error_reason()}
  def device_to_user_distance(%Ref{} = context, dx, dy) do
    context.port
    |> CairoPort.command({:device_to_user_distance, [context.handle, dx / 1, dy / 1]})
    |> case do
      {:ok, [dx1, dy1]} -> {:ok, {dx1, dy1}}
      error -> error
    end
  end

  @spec get_matrix(context :: Ref.t()) :: Matrix.t()
  def get_matrix(%Ref{} = context) do
    case CairoPort.command(context.port, {:get_matrix, [context.handle]}) do
      {:ok, m} -> {:ok, Matrix.from_list(m)}
      error -> error
    end
  end

  @spec translate(context :: Ref.t(), x :: float(), y :: float()) :: Ref.t()
  def translate(%Ref{} = context, x, y) do
    chained_command(context, {:translate, [context.handle, x / 1, y / 1]})
  end

  @spec scale(context :: Ref.t(), sx :: float(), sy :: float()) :: Ref.t()
  def scale(%Ref{} = context, sx, sy) do
    chained_command(context, {:scale, [context.handle, sx / 1, sy / 1]})
  end

  @spec rotate(context :: Ref.t(), angle :: float()) :: Ref.t()
  def rotate(%Ref{} = context, angle) do
    chained_command(context, {:rotate, [context.handle, angle / 1]})
  end

  @spec transform(context :: Ref.t(), matrix :: Matrix.t()) :: Ref.t()
  def transform(%Ref{} = context, matrix) do
    m = matrix |> Matrix.to_float() |> Matrix.to_list()
    chained_command(context, {:transform, [context.handle, m]})
  end

  @spec set_matrix(context :: Ref.t(), matrix :: Matrix.t()) :: Ref.t()
  def set_matrix(%Ref{} = context, matrix) do
    m = matrix |> Matrix.to_float() |> Matrix.to_list()
    chained_command(context, {:set_matrix, [context.handle, m]})
  end

  @spec identity_matrix(context :: Ref.t()) :: Ref.t()
  def identity_matrix(%Ref{} = context) do
    chained_command(context, {:identity_matrix, [context.handle]})
  end

  @spec set_source_rgb(context :: Ref.t(), r :: float(), g :: float(), b :: float()) :: Ref.t()
  def set_source_rgb(%Ref{} = context, r, g, b) do
    chained_command(context, {:set_source_rgb, [context.handle, r / 1, g / 1, b / 1]})
  end

  @spec set_source_rgba(
          context :: Ref.t(),
          r :: float(),
          g :: float(),
          b :: float(),
          a :: float()
        ) :: Ref.t()
  def set_source_rgba(%Ref{} = context, r, g, b, a) do
    chained_command(context, {:set_source_rgba, [context.handle, r / 1, g / 1, b / 1, a / 1]})
  end

  @spec arc(
          context :: Ref.t(),
          xc :: float(),
          yc :: float(),
          radius :: float(),
          angle1 :: float(),
          angle2 :: float()
        ) :: Ref.t()
  def arc(%Ref{} = context, xc, yc, radius, angle1, angle2) do
    chained_command(
      context,
      {:arc, [context.handle, xc / 1, yc / 1, radius / 1, angle1 / 1, angle2 / 1]}
    )
  end

  @spec rectangle(
          context :: Ref.t(),
          x :: float(),
          y :: float(),
          width :: float(),
          height :: float()
        ) :: Ref.t()
  def rectangle(%Ref{} = context, x, y, width, height) do
    chained_command(context, {:rectangle, [context.handle, x / 1, y / 1, width / 1, height / 1]})
  end

  @spec paint(context :: Ref.t()) :: Ref.t()
  def paint(%Ref{} = context) do
    chained_command(context, {:paint, [context.handle]})
  end

  @spec fill(context :: Ref.t()) :: Ref.t()
  def fill(%Ref{} = context) do
    chained_command(context, {:fill, [context.handle]})
  end

  @spec line_to(context :: Ref.t(), x :: float(), y :: float()) :: Ref.t()
  def line_to(%Ref{} = context, x, y) do
    chained_command(context, {:line_to, [context.handle, x / 1, y / 1]})
  end

  @spec move_to(context :: Ref.t(), x :: float(), y :: float()) :: Ref.t()
  def move_to(%Ref{} = context, x, y) do
    chained_command(context, {:move_to, [context.handle, x / 1, y / 1 / 1]})
  end

  @spec set_line_width(context :: Ref.t(), width :: float()) :: Ref.t()
  def set_line_width(%Ref{} = context, width) do
    chained_command(context, {:set_line_width, [context.handle, width / 1]})
  end

  @spec stroke(context :: Ref.t()) :: Ref.t()
  def stroke(%Ref{} = context) do
    chained_command(context, {:stroke, [context.handle]})
  end

  @spec save(context :: Ref.t()) :: Ref.t()
  def save(%Ref{} = context) do
    chained_command(context, {:save, [context.handle]})
  end

  @spec restore(context :: Ref.t()) :: Ref.t()
  def restore(%Ref{} = context) do
    chained_command(context, {:restore, [context.handle]})
  end

  @spec push_group(context :: Ref.t()) :: Ref.t()
  def push_group(%Ref{} = context) do
    chained_command(context, {:push_group, [context.handle]})
  end

  @spec pop_group(context :: Ref.t()) :: Ref.t()
  def pop_group(%Ref{} = context) do
    chained_command(context, {:pop_group, [context.handle]})
  end

  @spec status(context :: Ref.t()) :: :ok | {:error, CairoEx.error_reason()}
  def status(%Ref{} = context) do
    CairoPort.command(context.port, {:status, [context.handle]})
  end

  @spec destroy(context :: Ref.t()) :: no_return()
  def destroy(%Ref{} = context) do
    chained_command(context, {:destroy, [context.handle]})
    nil
  end

  defp chained_command(%Ref{type: :context, port: port} = context, cmd) do
    case CairoPort.command(port, cmd) do
      :ok ->
        context

      result ->
        raise CairoEx.Error, message: "Unexpected result: #{inspect(result)}"
    end
  end
end

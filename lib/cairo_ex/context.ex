defmodule CairoEx.Context do
  @moduledoc """
  Context is the main module used for drawing.
  """

  alias CairoEx.{
    CairoPort,
    Matrix,
    Ref
  }

  @doc """
  Create a new context from a surface
  """
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

  @doc """
  Gets the target surface associated with the context
  """
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

  @doc """
  Transform a coordinate from user space to device space by multiplying the given point by the current transformation matrix (CTM).
  """
  @spec user_to_device(context :: Ref.t(), x :: float(), y :: float()) ::
          {:ok, CairoEx.vector()} | {:error, CairoEx.error_reason()}
  def user_to_device(%Ref{} = context, x, y)
      when is_float(x) and is_float(y) do
    context.port
    |> CairoPort.command({:user_to_device, [context.handle, x, y]})
    |> case do
      {:ok, [x1, y1]} -> {:ok, {x1, y1}}
      error -> error
    end
  end

  @doc """
  Transform a distance vector from user space to device space.
  """
  @spec user_to_device_distance(context :: Ref.t(), dx :: float(), dy :: float()) ::
          {:ok, CairoEx.vector()} | {:error, CairoEx.error_reason()}
  def user_to_device_distance(%Ref{} = context, dx, dy)
      when is_float(dx) and is_float(dy) do
    context.port
    |> CairoPort.command({:user_to_device_distance, [context.handle, dx, dy]})
    |> case do
      {:ok, [dx1, dy1]} -> {:ok, {dx1, dy1}}
      error -> error
    end
  end

  @doc """
  Transform a coordinate from device space to user space by multiplying the given point by the inverse of the current transformation matrix (CTM).
  """
  @spec device_to_user(context :: Ref.t(), x :: float(), y :: float()) ::
          {:ok, CairoEx.vector()} | {:error, CairoEx.error_reason()}
  def device_to_user(%Ref{} = context, x, y)
      when is_float(x) and is_float(y) do
    context.port
    |> CairoPort.command({:device_to_user, [context.handle, x, y]})
    |> case do
      {:ok, [x1, y1]} -> {:ok, {x1, y1}}
      error -> error
    end
  end

  @doc """
  Transform a distance vector from device space to user space.
  """
  @spec device_to_user_distance(context :: Ref.t(), dx :: float(), dy :: float()) ::
          {:ok, CairoEx.vector()} | {:error, CairoEx.error_reason()}
  def device_to_user_distance(%Ref{} = context, dx, dy)
      when is_float(dx) and is_float(dy) do
    context.port
    |> CairoPort.command({:device_to_user_distance, [context.handle, dx, dy]})
    |> case do
      {:ok, [dx1, dy1]} -> {:ok, {dx1, dy1}}
      error -> error
    end
  end

  @doc """
  Returns the current transformation matrix (CTM).
  """
  @spec get_matrix(context :: Ref.t()) :: Matrix.t()
  def get_matrix(%Ref{} = context) do
    case CairoPort.command(context.port, {:get_matrix, [context.handle]}) do
      {:ok, m} -> {:ok, Matrix.from_list(m)}
      error -> error
    end
  end

  @doc """
  Modifies the current transformation matrix (CTM) by translating the user-space origin by (tx, ty).
  """
  @spec translate(context :: Ref.t(), tx :: float(), ty :: float()) :: Ref.t()
  def translate(%Ref{} = context, tx, ty)
      when is_float(tx) and is_float(ty) do
    chained_command(context, {:translate, [context.handle, tx, ty]})
  end

  @doc """
  Modifies the current transformation matrix (CTM) by scaling the X and Y user-space axes by sx and sy respectively.
  """
  @spec scale(context :: Ref.t(), sx :: float(), sy :: float()) :: Ref.t()
  def scale(%Ref{} = context, sx, sy)
      when is_float(sx) and is_float(sy) do
    chained_command(context, {:scale, [context.handle, sx, sy]})
  end

  @doc """
  Modifies the current transformation matrix (CTM) by rotating the user-space axes by angle radians.
  """
  @spec rotate(context :: Ref.t(), angle :: float()) :: Ref.t()
  def rotate(%Ref{} = context, angle)
      when is_float(angle) do
    chained_command(context, {:rotate, [context.handle, angle]})
  end

  @doc """
  Modifies the current transformation matrix (CTM) by applying matrix as an additional transformation.
  """
  @spec transform(context :: Ref.t(), matrix :: Matrix.t()) :: Ref.t()
  def transform(%Ref{} = context, matrix) do
    m = matrix |> Matrix.to_float() |> Matrix.to_list()
    chained_command(context, {:transform, [context.handle, m]})
  end

  @doc """
  Set the current transformation matrix (CTM).
  """
  @spec set_matrix(context :: Ref.t(), matrix :: Matrix.t()) :: Ref.t()
  def set_matrix(%Ref{} = context, matrix) do
    m = matrix |> Matrix.to_float() |> Matrix.to_list()
    chained_command(context, {:set_matrix, [context.handle, m]})
  end

  @doc """
  Resets the current transformation matrix (CTM) by setting it equal to the identity matrix.
  """
  @spec identity_matrix(context :: Ref.t()) :: Ref.t()
  def identity_matrix(%Ref{} = context) do
    chained_command(context, {:identity_matrix, [context.handle]})
  end

  @doc """
  Sets the source pattern within the context to an opaque color.
  """
  @spec set_source_rgb(context :: Ref.t(), r :: float(), g :: float(), b :: float()) :: Ref.t()
  def set_source_rgb(%Ref{} = context, r, g, b)
      when is_float(r) and is_float(g) and is_float(b) do
    chained_command(context, {:set_source_rgb, [context.handle, r, g, b]})
  end

  @doc """
  Sets the source pattern within the context to a translucent color.
  """
  @spec set_source_rgba(
          context :: Ref.t(),
          r :: float(),
          g :: float(),
          b :: float(),
          a :: float()
        ) :: Ref.t()
  def set_source_rgba(%Ref{} = context, r, g, b, a)
      when is_float(r) and is_float(g) and is_float(b) and is_float(a) do
    chained_command(context, {:set_source_rgba, [context.handle, r, g, b, a]})
  end

  @doc """
  Adds a circular arc of the given radius to the current path.
  """
  @spec arc(
          context :: Ref.t(),
          xc :: float(),
          yc :: float(),
          radius :: float(),
          angle1 :: float(),
          angle2 :: float()
        ) :: Ref.t()
  def arc(%Ref{} = context, xc, yc, radius, angle1, angle2)
      when is_float(xc) and
             is_float(yc) and
             is_float(radius) and
             is_float(angle1) and
             is_float(angle2) do
    chained_command(
      context,
      {:arc, [context.handle, xc, yc, radius, angle1, angle2]}
    )
  end

  @doc """
  Adds a closed-subpath rectangle of the given size to the current path at position (x, y) in user-space coordinates.
  """
  @spec rectangle(
          context :: Ref.t(),
          x :: float(),
          y :: float(),
          width :: float(),
          height :: float()
        ) :: Ref.t()
  def rectangle(%Ref{} = context, x, y, width, height)
      when is_float(x) and
             is_float(y) and
             is_float(width) and
             is_float(height) do
    chained_command(context, {:rectangle, [context.handle, x, y, width, height]})
  end

  @doc """
  A drawing operator that paints the current source everywhere within the current clip region.
  """
  @spec paint(context :: Ref.t()) :: Ref.t()
  def paint(%Ref{} = context) do
    chained_command(context, {:paint, [context.handle]})
  end

  @doc """
  A drawing operator that fills the current path according to the current fill rule, (each sub-path is implicitly closed before being filled).
  """
  @spec fill(context :: Ref.t()) :: Ref.t()
  def fill(%Ref{} = context) do
    chained_command(context, {:fill, [context.handle]})
  end

  @doc """
  Adds a line to the path from the current point to position (x, y) in user-space coordinates.
  """
  @spec line_to(context :: Ref.t(), x :: float(), y :: float()) :: Ref.t()
  def line_to(%Ref{} = context, x, y) do
    chained_command(context, {:line_to, [context.handle, x / 1, y / 1]})
  end

  @doc """
  If the current subpath is not empty, begin a new subpath.
  """
  @spec move_to(context :: Ref.t(), x :: float(), y :: float()) :: Ref.t()
  def move_to(%Ref{} = context, x, y)
      when is_float(x) and is_float(y) do
    chained_command(context, {:move_to, [context.handle, x, y]})
  end

  @doc """
  Sets the current line width within the cairo context.
  """
  @spec set_line_width(context :: Ref.t(), width :: float()) :: Ref.t()
  def set_line_width(%Ref{} = context, width)
      when is_float(width) do
    chained_command(context, {:set_line_width, [context.handle, width]})
  end

  @doc """
  A drawing operator that strokes the current Path according to the current line width, line join, line cap, and dash settings.
  """
  @spec stroke(context :: Ref.t()) :: Ref.t()
  def stroke(%Ref{} = context) do
    chained_command(context, {:stroke, [context.handle]})
  end

  @doc """
  Makes a copy of the current state of the context and saves it on an internal stack of saved states.
  """
  @spec save(context :: Ref.t()) :: Ref.t()
  def save(%Ref{} = context) do
    chained_command(context, {:save, [context.handle]})
  end

  @doc """
  Restores cr to the state saved by a preceding call to save/1 and removes
  that state from the stack of saved states.
  """
  @spec restore(context :: Ref.t()) :: Ref.t()
  def restore(%Ref{} = context) do
    chained_command(context, {:restore, [context.handle]})
  end

  @doc """
  Temporarily redirects drawing to an intermediate surface known as a group.
  The redirection lasts until the group is completed by a call to Context.pop_group/1 or
  Context.pop_group_to_source/1. These calls provide the result of any drawing to the group as a
  pattern.
  """
  @spec push_group_with_content(context :: Ref.t(), content :: CairoEx.content()) :: Ref.t()
  def push_group_with_content(%Ref{} = context, content) when is_atom(content) do
    chained_command(context, {:push_group_with_content, [context.handle, content]})
  end

  @doc """
  Terminates the redirection begun by a call to Context.push_group/1 or Context.push_group_with_content/2
  and returns a new pattern containing the results of all drawing operations performed to the group.
  """
  @spec pop_group(context :: Ref.t()) :: {:ok, Ref.t()}
  def pop_group(%Ref{} = context) do
    case CairoPort.command(context.port, {:pop_group, [context.handle]}) do
      {:ok, handle} -> {:ok, Ref.make(handle, :pattern, context.port)}
      error -> error
    end
  end

  @doc """
  Terminates the redirection begun by a call to Context.push_group/1 or Context.push_group_with_content/2
  and installs the resulting pattern as the source pattern in the given context.
  """
  @spec push_group(context :: Ref.t()) :: Ref.t()
  def pop_group_to_source(%Ref{} = context) do
    chained_command(context, {:pop_group_to_source, [context.handle]})
  end

  @doc """
  Temporarily redirects drawing to an intermediate surface known as a group.
  """
  @spec push_group(context :: Ref.t()) :: Ref.t()
  def push_group(%Ref{} = context) do
    chained_command(context, {:push_group, [context.handle]})
  end

  @doc """
  Sets the dash pattern to be used by Context.stroke/1. A dash pattern is specified by dashes, an array of
  positive values. Each value provides the length of alternate "on" and "off" portions of the stroke.
  The offset specifies an offset into the pattern at which the stroke begins.
  """
  @spec set_dash(context :: Ref.t(), list(float()), offset :: float()) :: Ref.t()
  def set_dash(%Ref{} = context, dashes, offset)
      when is_list(dashes) and is_float(offset) do
    chained_command(context, {:set_dash, [context.handle, dashes, offset]})
  end

  @spec set_antialias(context :: Ref.t(), antialias :: CairoEx.antialias()) :: Ref.t()
  def set_antialias(%Ref{} = context, antialias)
      when is_atom(antialias) do
    chained_command(context, {:set_antialias, [context.handle, antialias]})
  end

  @spec get_antialias(context :: Ref.t()) ::
          {:ok, CairoEx.antialias()} | {:error, CairoEx.error_reason()}
  def get_antialias(%Ref{} = context) do
    context.port
    |> CairoPort.command({:get_antialias, [context.handle]})
    |> case do
      {:ok, antialias} -> {:ok, antialias}
      error -> error
    end
  end

  @doc """
  Returns the last error, if any.
  """
  @spec status(context :: Ref.t()) :: :ok | {:error, CairoEx.error_reason()}
  def status(%Ref{} = context) do
    CairoPort.command(context.port, {:status, [context.handle]})
  end

  @doc """
  Destroys the context
  """
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

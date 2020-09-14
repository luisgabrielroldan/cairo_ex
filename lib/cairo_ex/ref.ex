defmodule CairoEx.Ref do
  @moduledoc false

  @typep handle :: integer()

  @typep type ::
           :surface
           | :context

  @type t :: %__MODULE__{
          handle: handle(),
          type: type(),
          port: pid()
        }

  defstruct [
    :type,
    :handle,
    :port
  ]

  @doc """
  Make reference
  """
  def make(handle, type, port)
      when is_integer(handle) and is_pid(port) and is_atom(type) do
    %__MODULE__{
      handle: handle,
      port: port,
      type: type
    }
  end

  defimpl Inspect do
    import Inspect.Algebra

    def inspect(ref, _opts) do
      concat([
        "#CairoEx.Ref<",
        to_string(ref.type),
        "::0x",
        Integer.to_string(ref.handle, 16),
        ">"
      ])
    end
  end
end

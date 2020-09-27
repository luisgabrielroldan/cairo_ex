defmodule CairoEx.Matrix do
  @moduledoc """
  A transformation matrix
  """

  @type t :: %__MODULE__{
          xx: number(),
          yx: number(),
          xy: number(),
          yy: number(),
          x0: number(),
          y0: number()
        }

  defstruct [
    :xx,
    :yx,
    :xy,
    :yy,
    :x0,
    :y0
  ]

  @spec new(
          xx :: number(),
          yx :: number(),
          xy :: number(),
          yy :: number(),
          x0 :: number(),
          y0 :: number()
        ) :: t()
  def new(xx, yx, xy, yy, x0, y0) do
    %__MODULE__{
      xx: xx,
      yx: yx,
      xy: xy,
      yy: yy,
      x0: x0,
      y0: y0
    }
  end

  @spec to_list(t()) :: list(number())
  def to_list(%__MODULE__{} = m) do
    [
      m.xx,
      m.yx,
      m.xy,
      m.yy,
      m.x0,
      m.y0
    ]
  end

  @spec from_list(list(number())) :: t()
  def from_list(list) when is_list(list) do
    [xx, yx, xy, yy, x0, y0] = list

    %__MODULE__{
      xx: xx,
      yx: yx,
      xy: xy,
      yy: yy,
      x0: x0,
      y0: y0
    }
  end

  @spec to_float(t()) :: t()
  def to_float(%__MODULE__{} = m) do
    %__MODULE__{
      xx: m.xx / 1,
      yx: m.yx / 1,
      xy: m.xy / 1,
      yy: m.yy / 1,
      x0: m.x0 / 1,
      y0: m.y0 / 1
    }
  end
end

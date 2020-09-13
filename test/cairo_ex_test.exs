defmodule CairoExTest do
  use ExUnit.Case

  alias CairoEx.{Context, Surface}

  test "proof of concept" do
    assert {:ok, cairo} = CairoEx.start_link()

    assert {:ok, surface} = Surface.image_surface_create(cairo, :rgb24, 320, 240)
    assert {:ok, context} = Context.create(cairo, surface)

    context
    |> Context.set_source_rgb(1.0, 1.0, 1.0)
    |> Context.paint()
    |> Context.move_to(50.0, 60.0)
    |> Context.line_to(200.0, 200.0)
    |> Context.set_line_width(6.0)
    |> Context.set_source_rgb(1.0, 0.0, 0.0)
    |> Context.stroke()

    assert :ok = Surface.write_to_png(surface, "/tmp/image.png")
    assert :ok = Surface.destroy(surface)
  end
end

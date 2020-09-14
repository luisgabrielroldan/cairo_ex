defmodule CairoExTest do
  use ExUnit.Case

  alias CairoEx.{Context, Surface}

  test "proof of concept" do
    assert {:ok, cairo} = CairoEx.start_link()

    assert {:ok, surface} = Surface.image_surface_create(cairo, :rgb24, 320, 240)
    assert {:ok, context} = Context.create(surface)

    context
    |> Context.set_source_rgb(1.0, 1.0, 1.0)
    |> Context.paint()
    |> Context.move_to(50.0, 60.0)
    |> Context.line_to(100.0, 100.0)
    |> Context.set_line_width(6.0)
    |> Context.set_source_rgb(1.0, 0.0, 0.0)
    |> Context.stroke()

    assert {:ok, ^surface} = Context.get_target(context)
    assert :ok = Context.destroy(context)
    assert :ok = Surface.write_to_png(surface, "/tmp/image.png")
    assert :ok = Surface.destroy(surface)
  end

  test "rectangles" do
    assert {:ok, cairo} = CairoEx.start_link()

    assert {:ok, surface} = Surface.image_surface_create(cairo, :rgb24, 270, 270)
    assert {:ok, context} = Context.create(surface)

    context
    |> Context.set_source_rgb(1.0, 1.0, 1.0)
    |> Context.paint()
    |> Context.set_source_rgb(0.5, 0.5, 1)
    |> Context.rectangle(20, 20, 100, 100)
    |> Context.fill()
    |> Context.set_source_rgb(0.6, 0.6, 0.6)
    |> Context.rectangle(150, 20, 100, 100)
    |> Context.fill()
    |> Context.set_source_rgb(0, 0.3, 0)
    |> Context.rectangle(20, 140, 100, 100)
    |> Context.fill()
    |> Context.set_source_rgb(1, 0, 0.5)
    |> Context.rectangle(150, 140, 100, 100)
    |> Context.fill()

    assert :ok = Surface.write_to_png(surface, "/tmp/image.png")
    assert :ok = Surface.destroy(surface)
  end
end

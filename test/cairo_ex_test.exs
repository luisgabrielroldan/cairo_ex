defmodule CairoExTest do
  use ExUnit.Case

  alias CairoEx.{Context, Surface}

  test "proof of concept" do
    assert {:ok, cairo} = CairoEx.start_link()

    # cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_RGB32, 240, 80);
    assert {:ok, surface} = Surface.image_surface_create(cairo, :rgb24, 320, 240)

    # cairo_create (surface);
    assert {:ok, context} = Context.create(cairo, surface)

    # set_source_rgb (context, 1.0, 1.0, 1.0);
    assert :ok = Context.set_source_rgb(context, 1.0, 1.0, 1.0)

    # cairo_paint (surface);
    assert :ok = Context.paint(context)

    # cairo_move_to (context, 50.0, 60.0);
    assert :ok = Context.move_to(context, 50.0, 60.0)

    # cairo_line_to (context, 200.0, 200.0);
    assert :ok = Context.line_to(context, 200.0, 200.0)

    # cairo_set_line_width (context, 6.0);
    assert :ok = Context.set_line_width(context, 6.0)

    # set_source_rgb (context, 1.0, 0.0, 0.0);
    assert :ok = Context.set_source_rgb(context, 1.0, 0.0, 0.0)

    # cairo_stroke (context);
    assert :ok = Context.stroke(context)

    # cairo_surface_write_to_png (surface, "/tmp/image.png");
    assert :ok = Surface.write_to_png(surface, "/tmp/image.png")

    # cairo_surface_destroy (surface);
    assert :ok = Surface.destroy(surface)
  end
end

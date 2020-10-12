defmodule CairoExTest do
  use ExUnit.Case

  alias CairoEx.{Context, Matrix, Surface}

  setup do
    {:ok, cairo} = CairoEx.start_link()

    {:ok, %{cairo: cairo}}
  end

  test "proof of concept", %{cairo: cairo} do
    assert {:ok, surface} = Surface.image_surface_create(cairo, :rgb24, 320, 240)
    assert {:ok, context} = Context.create(surface)

    context
    |> Context.set_antialias(:best)
    |> Context.set_source_rgb(1.0, 1.0, 1.0)
    |> Context.paint()
    |> Context.move_to(50.0, 60.0)
    |> Context.line_to(100.0, 100.0)
    |> Context.set_line_width(6.0)
    |> Context.set_source_rgb(1.0, 0.0, 0.0)
    |> Context.set_dash([1.0, 5.0], 0.0)
    |> Context.stroke()

    assert {:ok, :best} = Context.get_antialias(context)

    assert {:ok, ^surface} = Context.get_target(context)
    Context.destroy(context)
    assert :ok = Surface.write_to_png(surface, "/tmp/image.png")
    Surface.destroy(surface)
  end

  test "rectangles", %{cairo: cairo} do
    assert {:ok, surface} = Surface.image_surface_create(cairo, :rgb24, 270, 270)
    assert {:ok, context} = Context.create(surface)

    context
    |> Context.paint()
    |> Context.set_source_rgb(0.5, 0.5, 1.0)
    |> Context.rectangle(20.0, 20.0, 100.0, 100.0)
    |> Context.fill()
    |> Context.set_source_rgb(0.6, 0.6, 0.6)
    |> Context.rectangle(150.0, 20.0, 100.0, 100.0)
    |> Context.fill()
    |> Context.set_source_rgb(0.0, 0.3, 0.0)
    |> Context.rectangle(20.0, 140.0, 100.0, 100.0)
    |> Context.fill()
    |> Context.set_source_rgb(1.0, 0.0, 0.5)
    |> Context.rectangle(150.0, 140.0, 100.0, 100.0)
    |> Context.fill()

    m = Matrix.new(2.0, 1.0, 3.0, 1.0, 0.0, 0.0)

    assert ^context = Context.set_matrix(context, m)

    assert {:ok, ^m} = Context.get_matrix(context)

    assert {:ok, {50.0, 20.0}} = Context.user_to_device(context, 10.0, 10.0)
    assert {:ok, {50.0, 20.0}} = Context.user_to_device_distance(context, 10.0, 10.0)
    assert {:ok, {10.0, 10.0}} = Context.device_to_user(context, 50.0, 20.0)
    assert {:ok, {10.0, 10.0}} = Context.device_to_user_distance(context, 50.0, 20.0)

    assert ^context = Context.identity_matrix(context)

    assert :ok = Surface.write_to_png(surface, "/tmp/image.png")
    Surface.destroy(surface)
  end
end

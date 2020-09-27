defmodule CairoEx.Context.TransformationsTest do
  use ExUnit.Case

  alias CairoEx.{Context, Matrix, Surface}

  setup do
    {:ok, cairo} = CairoEx.start_link()
    {:ok, surface} = Surface.image_surface_create(cairo, :rgb24, 320, 240)
    {:ok, context} = Context.create(surface)

    {:ok, %{context: context}}
  end

  test "get_matrix", %{context: context} do
    assert {:ok, %Matrix{xx: 1.0, x0: 0.0, xy: 0.0, y0: 0.0, yx: 0.0, yy: 1.0}} =
             Context.get_matrix(context)
  end

  test "set_matrix", %{context: context} do
    m = %Matrix{xx: 1.0, x0: 3.0, xy: 0.0, y0: 2.0, yx: 0.0, yy: 1.0}

    assert ^context = Context.set_matrix(context, m)

    assert {:ok, %Matrix{x0: 3.0, xx: 1.0, xy: 0.0, y0: 2.0, yx: 0.0, yy: 1.0}} =
             Context.get_matrix(context)
  end

  test "identity_matrix", %{context: context} do
    assert ^context = Context.identity_matrix(context)

    assert {:ok, %Matrix{xx: 1.0, x0: 0.0, xy: 0.0, y0: 0.0, yx: 0.0, yy: 1.0}} =
             Context.get_matrix(context)
  end

  test "translate", %{context: context} do
    assert ^context = Context.translate(context, 1.0, 2.0)

    assert {:ok, %Matrix{xx: 1.0, x0: 1.0, xy: 0.0, y0: 2.0, yx: 0.0, yy: 1.0}} =
             Context.get_matrix(context)
  end

  test "scale", %{context: context} do
    assert ^context = Context.scale(context, 2.0, 3.0)

    assert {:ok, %Matrix{x0: 0.0, xx: 2.0, xy: 0.0, y0: 0.0, yx: 0.0, yy: 3.0}} =
             Context.get_matrix(context)
  end

  test "rotate", %{context: context} do
    assert ^context = Context.rotate(context, 3.16)

    assert {:ok,
            %Matrix{
              x0: 0.0,
              xx: -0.9998305895825983,
              xy: 0.01840630693305381,
              y0: 0.0,
              yx: -0.01840630693305381,
              yy: -0.9998305895825983
            }} = Context.get_matrix(context)
  end

  test "transform", %{context: context} do
    m = %Matrix{xx: 1.0, x0: 3.0, xy: 0.0, y0: 2.0, yx: 0.0, yy: 1.0}

    assert ^context = Context.transform(context, m)

    assert {:ok, %Matrix{x0: 3.0, xx: 1.0, xy: 0.0, y0: 2.0, yx: 0.0, yy: 1.0}} =
             Context.get_matrix(context)
  end

  test "user_to_device", %{context: context} do
    m = %Matrix{xx: 1.0, x0: 3.0, xy: 0.0, y0: 2.0, yx: 0.0, yy: 1.0}
    assert ^context = Context.set_matrix(context, m)
    assert {:ok, {13.0, 12.0}} = Context.user_to_device(context, 10.0, 10.0)
  end

  test "user_to_device_distance", %{context: context} do
    m = %Matrix{xx: 1.0, x0: 3.0, xy: 1.0, y0: 2.0, yx: 0.0, yy: 1.0}
    assert ^context = Context.set_matrix(context, m)
    assert {:ok, {20.0, 10.0}} = Context.user_to_device_distance(context, 10.0, 10.0)
  end

  test "device_to_user", %{context: context} do
    m = %Matrix{xx: 1.0, x0: 3.0, xy: 0.0, y0: 2.0, yx: 0.0, yy: 1.0}
    assert ^context = Context.set_matrix(context, m)
    assert {:ok, {7.0, 8.0}} = Context.device_to_user(context, 10.0, 10.0)
  end

  test "device_to_user_distance", %{context: context} do
    m = %Matrix{xx: 1.0, x0: 3.0, xy: 1.0, y0: 2.0, yx: 2.0, yy: 1.0}
    assert ^context = Context.set_matrix(context, m)
    assert {:ok, {0.0, 10.0}} = Context.device_to_user_distance(context, 10.0, 10.0)
  end
end

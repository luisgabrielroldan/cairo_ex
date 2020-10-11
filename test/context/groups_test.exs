defmodule CairoEx.Context.GroupsTests do
  use ExUnit.Case

  alias CairoEx.{Ref, Context, Surface}

  setup do
    {:ok, cairo} = CairoEx.start_link()
    {:ok, surface} = Surface.image_surface_create(cairo, :rgb24, 320, 240)
    {:ok, context} = Context.create(surface)

    {:ok, %{context: context}}
  end

  test "push_group/1 & pop_group/1", %{context: context} do
    assert {:ok, %Ref{}} =
             context
             |> Context.push_group()
             |> Context.pop_group()
  end

  test "pop_group_to_source/1", %{context: context} do
    assert context ==
             context
             |> Context.push_group()
             |> Context.pop_group_to_source()

    assert :ok = Context.status(context)
  end

  test "push_group_with_content/1", %{context: context} do
    assert {:ok, %Ref{}} =
             context
             |> Context.push_group_with_content(:color)
             |> Context.pop_group()
  end
end

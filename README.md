# CairoEx

[![Actions Status](https://github.com/luisgabrielroldan/cairo_ex/workflows/Tests/badge.svg)](https://github.com/luisgabrielroldan/cairo_ex/actions)
[![Hex version](https://img.shields.io/hexpm/v/cairo_ex.svg "Hex version")](https://hex.pm/packages/cairo_ex)


Cairo wrapper for Elixir.

*(THIS IS WORK IN PROGRESS)*

## Usage
```elixir
  {:ok, cairo} = CairoEx.start_link()

  {:ok, surface} = Surface.image_surface_create(cairo, :rgb24, 270, 270)
  {:ok, context} = Context.create(surface)

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

  :ok = Surface.write_to_png(surface, "/tmp/output.png")
  :ok = Surface.destroy(surface)
```

Output:

![Result image](img/rects.png)


## Installation

If [available in Hex](https://hex.pm/docs/publish), the package can be installed
by adding `cairo_ex` to your list of dependencies in `mix.exs`:

```elixir
def deps do
  [
    {:cairo_ex, "~> 0.1.0"}
  ]
end
```

Documentation can be generated with [ExDoc](https://github.com/elixir-lang/ex_doc)
and published on [HexDocs](https://hexdocs.pm). Once published, the docs can
be found at [https://hexdocs.pm/cairo_ex](https://hexdocs.pm/cairo_ex).


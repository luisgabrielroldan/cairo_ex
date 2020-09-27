defmodule CairoEx do
  @moduledoc """
  Documentation for `CairoEx`.
  """

  alias CairoEx.CairoPort

  @type t :: CairoPort.t()

  @type vector :: {x :: float(), y :: float()}

  @type format ::
          :invalid
          | :argb32
          | :rgb24
          | :a8
          | :a1
          | :rgb16_565
          | :rgb30

  @type ex_error_error ::
          :cx_invalid_reference
          | :cx_unknown_cmd
          | :cx_decode
          | :cx_encode

  @type error_reason ::
          :no_memory
          | :invalid_restore
          | :invalid_pop_group
          | :no_current_point
          | :invalid_matrix
          | :invalid_status
          | :null_pointer
          | :invalid_string
          | :invalid_path_data
          | :read_error
          | :write_error
          | :surface_finished
          | :surface_type_mismatch
          | :pattern_type_mismatch
          | :invalid_content
          | :invalid_format
          | :invalid_visual
          | :file_not_found
          | :invalid_dash
          | :invalid_dsc_comment
          | :invalid_index
          | :clip_not_representable
          | :temp_file_error
          | :invalid_stride
          | :font_type_mismatch
          | :user_font_immutable
          | :user_font_error
          | :negative_count
          | :invalid_clusters
          | :invalid_slant
          | :invalid_weight
          | :invalid_size
          | :user_font_not_implemented
          | :device_type_mismatch
          | :device_error
          | :invalid_mesh_construction
          | :device_finished
          | :jbig2_global_missing

  @spec start_link(args :: Keyword.t()) :: {:ok, t()} | {:error, t()}
  def start_link(args \\ []) do
    CairoPort.start_link(args)
  end
end

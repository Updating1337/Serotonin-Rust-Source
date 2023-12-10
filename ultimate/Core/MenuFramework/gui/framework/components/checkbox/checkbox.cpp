#include "../../calliope.hpp"

const calliope::color_t checkbox_hovered_color( 126, 126, 126, 255 );
const calliope::color_t checkbox_normal_color( 74, 74, 74, 255 );

const calliope::color_t checkbox_description_color( 44, 44, 44, 255 );
const calliope::color_t checkbox_hovered_description_color( 160, 160, 160, 255 );

void calliope::menu_t::components_t::checkbox( const char* name, bool& value, std::optional< component_info_t > description ) {
	if ( !menu.m_current_groupbox )
		return;

	auto checkbox_position = menu.m_current_groupbox->cursor_position + vec2_t( 0, 2 );
	const auto checkbox_size = vec2_t(10, 10 );

	const auto text_size = menu.drawing.calc_text_size( name );

	const bool was_empty_last_hash = menu.window_ctx.m_last_hash == 0 && menu.window_ctx.m_active_hash == 0;
	const bool active = menu.window_ctx.m_active_hash == util::hash( name );

	const bool hovered = menu.mouse_in_rect( checkbox_position, checkbox_position + checkbox_size + vec2_t( text_size.x, 0 ) );

	if ( hovered && !active && was_empty_last_hash && ( menu.mouse_active && !menu.old_mouse_active ) ) {
		menu.window_ctx.m_active_hash = util::hash( name );
	}
	else if ( active && !menu.mouse_active ) {
		menu.window_ctx.m_active_hash = 0;
		value = !value;
	}

	menu.drawing.filled_rect( checkbox_position, checkbox_size, color_t( 32, 32, 32, 255 ), 0.f );

	if ( value )
		menu.drawing.multi_color_filled_rect( checkbox_position, checkbox_size, { globals::menu_accent, globals::menu_accent, globals::menu_accent.darker( 50 ), globals::menu_accent.darker( 50 ) } );

	menu.drawing.rect( checkbox_position, checkbox_size, globals::palette::black, 0.f );

	menu.drawing.text( vec2_t( checkbox_position.x + checkbox_size.x + 7, checkbox_position.y + ( checkbox_size.y / 2.f - text_size.y / 2.f )  ), name, value ? globals::palette::white : ( hovered ? checkbox_hovered_color : checkbox_normal_color ), text_flags::text_flags_none );

	if ( description.has_value( ) ) {
		auto end_of_checkbox_position = vec2_t( checkbox_position.x + checkbox_size.x + 7 + text_size.x + 3, checkbox_position.y + ( checkbox_size.y / 2.f - text_size.y / 2.f ) );

		auto question_mark_sz = menu.drawing.calc_text_size( "(?)" );

		const bool hovered = menu.mouse_in_rect( end_of_checkbox_position, end_of_checkbox_position + question_mark_sz );

		menu.drawing.text( end_of_checkbox_position, "(?)", hovered ? checkbox_hovered_description_color : checkbox_description_color, text_flags::text_flags_style_dropshadow );

		if ( hovered && menu.window_ctx.m_active_hash == 0 ) {
			auto overlay_window_position = end_of_checkbox_position + question_mark_sz;
			auto overlay_window_size = menu.drawing.calc_text_size( description.value( ).description ) + vec2_t( 8, 8 );

			menu.draw_list.filled_rect( overlay_window_position, overlay_window_size, color_t( 8, 8, 8, 255 ), 3.f );

			menu.draw_list.text( overlay_window_position + vec2_t( 4, 4 ), description.value( ).description, globals::palette::white, text_flags::text_flags_style_dropshadow );

			menu.draw_list.rect( overlay_window_position + vec2_t( 1, 1 ), overlay_window_size - vec2_t( 2, 2 ), color_t( 32, 32, 32, 255 ), 3.f );
			menu.draw_list.rect( overlay_window_position, overlay_window_size, globals::palette::black, 3.f );
		}
	}

	menu.m_current_groupbox->cursor_position.y += max( checkbox_size.y * 0.f, text_size.y - 1.f );
}
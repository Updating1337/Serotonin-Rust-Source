#include "../../calliope.hpp"

const calliope::color_t dropdown_top_color( 24, 24, 24, 255 );
const calliope::color_t dropdown_bottom_color( 16, 16, 16, 255 );
const calliope::color_t dropdown_background_color( 18, 18, 18, 255 );

const calliope::color_t dropdown_text_hovered( 126, 126, 126, 255 );

void calliope::menu_t::components_t::dropdown( const char* name, std::vector< const char* > items, int& value ) {
	if ( !menu.m_current_groupbox )
		return;

	auto dropdown_position = menu.m_current_groupbox->cursor_position + vec2_t( 0, 17 );
	const auto dropdown_size = vec2_t( menu.m_current_groupbox->size.x - 54, 20 );

	menu.drawing.multi_color_filled_rect( dropdown_position, dropdown_size, { dropdown_top_color, dropdown_top_color, dropdown_bottom_color, dropdown_bottom_color } );
	menu.drawing.rect( dropdown_position, dropdown_size, color_t( 0, 0, 0, 255 ), 0.f );

	const bool was_empty_last_hash = menu.window_ctx.m_last_hash == 0 && menu.window_ctx.m_active_hash == 0;
	const bool hovered = menu.mouse_in_rect( dropdown_position, dropdown_position + dropdown_size );

	color_t label_color = color_t( 74, 74, 74, 255 );

	if ( hovered )
		label_color = dropdown_text_hovered;

	if ( hovered && ( menu.mouse_active && !menu.old_mouse_active ) && was_empty_last_hash ) {
		menu.window_ctx.m_active_hash = Hash( name, false );
	}

	else if ( menu.window_ctx.m_active_hash == Hash( name, false ) ) {
		label_color = globals::palette::white;

		if ( !menu.mouse_in_rect( dropdown_position, dropdown_position + dropdown_size + vec2_t( 0, items.size( ) * dropdown_size.y ) ) && ( menu.mouse_active && !menu.old_mouse_active ) ) {
			menu.window_ctx.m_active_hash = 0;
		}

		menu.draw_list.filled_rect( dropdown_position + vec2_t( 0, dropdown_size.y ), vec2_t( dropdown_size.x, items.size( ) * dropdown_size.y ), dropdown_background_color );

		for ( auto i{ 0 }; i < items.size( ); i++ ) {
			const bool item_hovered = menu.mouse_in_rect( dropdown_position + vec2_t( 0, dropdown_size.y + ( i * dropdown_size.y ) ), dropdown_position + vec2_t( dropdown_size.x, dropdown_size.y + ( i * dropdown_size.y ) + dropdown_size.y - 2 ) );

			if ( item_hovered ) {
				if ( menu.mouse_active && !menu.old_mouse_active ) {
					value = i;
					menu.window_ctx.m_active_hash = 0;
				}

				menu.draw_list.filled_rect( dropdown_position + vec2_t( 0, dropdown_size.y + ( i * dropdown_size.y ) ), dropdown_size, color_t( 24, 24, 24, 255 ) );
			}

			auto item_text_sz = menu.drawing.calc_text_size( items.at( i ) );

			menu.draw_list.text( dropdown_position + vec2_t( 5, dropdown_size.y + ( i * dropdown_size.y ) + ( item_text_sz.y / 2 ) - 7 ), items.at( i ), value == i ? globals::menu_accent : ( item_hovered ? color_t( 84, 84, 84, 255 ) :  color_t( 54, 54, 54, 255 ) ), text_flags::text_flags_none );
		}

		menu.draw_list.rect( dropdown_position + vec2_t( 0, dropdown_size.y ), vec2_t( dropdown_size.x, items.size( ) * dropdown_size.y ), color_t( 0, 0, 0, 255 ) );
	}

	auto label_text_sz = menu.drawing.calc_text_size( items.at( value ) );
	auto name_text_sz = menu.drawing.calc_text_size( name );

	menu.drawing.text( dropdown_position + vec2_t( 5, ( dropdown_size.y / 2 ) - ( label_text_sz.y / 2 )), items.at( value ), label_color, text_flags::text_flags_none );
	menu.drawing.text( dropdown_position - vec2_t( -2, dropdown_size.y - ( name_text_sz.y / 2 ) + 5 ), name, label_color, text_flags::text_flags_none );

	menu.m_current_groupbox->cursor_position.y += ( dropdown_size.y * 2 ) + 5;
}

void calliope::menu_t::components_t::multi_dropdown( const char* name, std::vector< const char* > items, std::vector< bool >& value ) {
	if ( !menu.m_current_groupbox )
		return;

	auto dropdown_position = menu.m_current_groupbox->cursor_position + vec2_t( 15, 15 );
	const auto dropdown_size = vec2_t( menu.m_current_groupbox->size.x - 54, 20 );

	bool in_use = menu.window_ctx.m_active_hash == util::hash( name );

	if ( in_use && !menu.mouse_in_rect( dropdown_position, dropdown_position + dropdown_size + vec2_t( 0, items.size( ) * dropdown_size.y ) ) && ( menu.mouse_active && !menu.old_mouse_active ) ) {
		menu.window_ctx.m_active_hash = 0;
	}

	std::string value_str;
	
	for ( int i = 0; i < value.size( ); i++ ) {
		if ( value.at( i ) ) {
			if ( value_str.size( ) > 0 )
				value_str += (", ");

			value_str += items.at( i );
		}
	}

	if ( !value_str.size( ) )
		value_str += ("-");

	menu.drawing.multi_color_filled_rect( dropdown_position, dropdown_size, { dropdown_top_color, dropdown_top_color, dropdown_bottom_color, dropdown_bottom_color } );

	const bool was_empty_last_hash = menu.window_ctx.m_last_hash == 0 && menu.window_ctx.m_active_hash == 0;
	const bool hovered = menu.mouse_in_rect( dropdown_position, dropdown_position + dropdown_size );

	color_t label_color = color_t( 54, 54, 54, 255 );

	if ( hovered )
		label_color = color_t( 160, 160, 160, 255 );

	if ( hovered && ( menu.mouse_active && !menu.old_mouse_active ) && was_empty_last_hash ) {
		menu.window_ctx.m_active_hash = Hash( name, false );
	}
	else if ( menu.window_ctx.m_active_hash == Hash( name, false ) ) {
		label_color = globals::palette::white;

		menu.draw_list.filled_rect( dropdown_position + vec2_t( 0, dropdown_size.y ), vec2_t( dropdown_size.x, items.size( ) * dropdown_size.y ), dropdown_background_color );

		for ( auto i{ 0 }; i < items.size( ); i++ ) {
			const bool item_hovered = menu.mouse_in_rect( dropdown_position + vec2_t( 0, dropdown_size.y + ( i * dropdown_size.y ) ), dropdown_position + vec2_t( dropdown_size.x, dropdown_size.y + ( i * dropdown_size.y ) + dropdown_size.y - 2 ) );

			if ( item_hovered ) {
				if ( menu.mouse_active && !menu.old_mouse_active ) {
					value.at( i ) = !value.at( i );
				}

				menu.draw_list.filled_rect( dropdown_position + vec2_t( 0, dropdown_size.y + ( i * dropdown_size.y ) ), dropdown_size, color_t( 24, 24, 24, 255 ) );
			}

			auto item_text_sz = menu.drawing.calc_text_size( items.at( i ) );

			menu.draw_list.text( dropdown_position + vec2_t( 5, dropdown_size.y + ( i * dropdown_size.y ) + ( item_text_sz.y / 2 ) - 7 ), items.at( i ), value.at( i ) ? globals::menu_accent : ( item_hovered ? color_t( 84, 84, 84, 255 ) : color_t( 54, 54, 54, 255 ) ), text_flags::text_flags_none );
		}

		menu.draw_list.rect( dropdown_position + vec2_t( 0, dropdown_size.y ), vec2_t( dropdown_size.x, items.size( ) * dropdown_size.y ), globals::palette::black );
	}

	auto value_text_sz = menu.drawing.calc_text_size( value_str.c_str( ) );
	auto name_text_sz = menu.drawing.calc_text_size( name );

	menu.drawing.push_clip_rect( dropdown_position, dropdown_position + dropdown_size - vec2_t( 5, 0 ), true );



	// todo add fade for overflow elements...
	//menu.drawing.multi_color_filled_rect( dropdown_position + vec2_t( dropdown_size.x - 30, 0 ), vec2_t( 30, dropdown_size.y ), { dropdown_top_color, dropdown_top_color, dropdown_bottom_color, dropdown_bottom_color } );

	menu.drawing.pop_clip_rect( );

	menu.drawing.rect( dropdown_position, dropdown_size, globals::palette::black, 0.f );

	menu.drawing.text(dropdown_position + vec2_t(5, (dropdown_size.y / 2) - (value_text_sz.y / 2)), value_str.c_str(), label_color, text_flags::text_flags_none);
	menu.drawing.text( dropdown_position - vec2_t( 0, dropdown_size.y - ( name_text_sz.y / 2 ) + 5), name, label_color, text_flags::text_flags_none );

	menu.m_current_groupbox->cursor_position.y += ( dropdown_size.y * 2 ) + 5;
}

void calliope::menu_t::components_t::sidecombo(const char* name, std::vector< const char* > items, int& value, vec2_t pos, vec2_t size) {
	//if (!menu.m_current_groupbox)
	//	return;

	auto dropdown_position = menu.window_ctx.drawable_area.first + pos;
	const auto dropdown_size = size;

	menu.drawing.multi_color_filled_rect(dropdown_position, dropdown_size, { color_t(16, 16, 16, 150), color_t(16, 16, 16, 150), color_t(8, 8, 8, 150), color_t(8, 8, 8, 150) });
	menu.drawing.rect(dropdown_position, dropdown_size, color_t(52, 52, 52, 255), 3.f);

	const bool was_empty_last_hash = menu.window_ctx.m_last_hash == 0 && menu.window_ctx.m_active_hash == 0;
	const bool hovered = menu.mouse_in_rect(dropdown_position, dropdown_position + dropdown_size);

	color_t label_color = color_t(74, 74, 74, 255);

	if (hovered)
		label_color = dropdown_text_hovered;

	auto label_text_sz = menu.drawing.calc_text_size(items.at(value));
	auto name_text_sz = menu.drawing.calc_text_size(name);
	int list_sz = items.size() - 1;

	const bool hovered_left = menu.mouse_in_rect(dropdown_position, dropdown_position + vec2_t(20, dropdown_size.y));
	color_t label_color_left = color_t(74, 74, 74, 255);
	if (hovered_left) {
		label_color_left = calliope::globals::menu_accent;

		if (menu.mouse_active && !menu.old_mouse_active) {
			value -= 1;
		}
	}

	const bool hovered_right = menu.mouse_in_rect(dropdown_position + vec2_t(dropdown_size.x - 20, 0), dropdown_position + dropdown_size);
	color_t label_color_right = color_t(74, 74, 74, 255);
	if (hovered_right) {
		label_color_right = calliope::globals::menu_accent;

		if (menu.mouse_active && !menu.old_mouse_active) {
			value += 1;
		}
	}

	if (value > list_sz)
	{
		value = 0;
	}

	//menu.drawing.text(dropdown_position + vec2_t(5, (dropdown_size.y / 2) - (label_text_sz.y / 2)), items.at(value), label_color, text_flags::text_flags_none);
	menu.drawing.text(dropdown_position + vec2_t(dropdown_size.x / 2 - (label_text_sz.x / 2), (dropdown_size.y / 2) - (label_text_sz.y / 2)), items.at(value), label_color, text_flags::text_flags_none);
	menu.drawing.text(dropdown_position - vec2_t(-5, 0), XS("<"), label_color_left, text_flags::text_flags_none);

	menu.drawing.text(dropdown_position + vec2_t(dropdown_size.x - 10, 0), XS(">"), label_color_right, text_flags::text_flags_none);

	menu.m_current_groupbox->cursor_position.y += (dropdown_size.y * 2) + 5;
}
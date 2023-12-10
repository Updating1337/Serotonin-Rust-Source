#include "../../calliope.hpp"

const calliope::color_t listbox_back_color( 18, 18, 18, 255 );

void calliope::menu_t::components_t::begin_listbox( const char* name, std::vector< const char* >& items, int& value, float height ) {
	if ( !menu.m_current_groupbox )
		return;

	auto current_listbox = menu.m_current_groupbox->get_listbox_by_name( name );
	if ( !current_listbox ) {
		current_listbox = new listbox_context_t( );

		current_listbox->m_id = name;
		
		current_listbox->position = menu.m_current_groupbox->cursor_position + vec2_t( 15, 0 );
		current_listbox->size = vec2_t( menu.m_current_groupbox->size.x - 54, 20 + height );
		current_listbox->m_item_count = items.size( );

		menu.m_current_groupbox->m_listboxes.push_back( current_listbox );
	}

	current_listbox->position = menu.m_current_groupbox->cursor_position + vec2_t( 15, 0 );
	current_listbox->size = vec2_t( menu.m_current_groupbox->size.x - 54, 20 + height );

	current_listbox->cursor_position = current_listbox->position + vec2_t( 0, 20 );

	int offset = static_cast< int >( current_listbox->old_cursor_position.y ) - static_cast< int >( static_cast< int >( current_listbox->position.y ) + static_cast< int >( current_listbox->size.y ) );

	if ( current_listbox->old_cursor_position.y > current_listbox->position.y + current_listbox->size.y ) {
		current_listbox->cursor_position.y -= static_cast< int >( offset * current_listbox->scroll_ratio );
	}

	menu.drawing.filled_rect( current_listbox->position, vec2_t( current_listbox->size.x, 20 ), listbox_back_color, 0.f );
	menu.drawing.rect( current_listbox->position, vec2_t( current_listbox->size.x, 20 ), globals::palette::black, 0.f );

	auto name_text_sz = menu.drawing.calc_text_size( name );
	menu.drawing.text( current_listbox->position + vec2_t( 5, 10 - ( name_text_sz.y / 2 )  ), name, color_t( 74, 74, 74, 255 ), text_flags::text_flags_none );

	menu.drawing.filled_rect( current_listbox->position + vec2_t( 0, 20 ), vec2_t( current_listbox->size.x, height ), listbox_back_color, 0.f );

	menu.drawing.push_clip_rect( current_listbox->position + vec2_t( 0, 19 ), vec2_t( current_listbox->position.x + current_listbox->size.x, current_listbox->position.y + 20 + height + 1 ), true );

	const bool was_empty_last_hash = menu.window_ctx.m_last_hash == 0 && menu.window_ctx.m_active_hash == 0;

	for ( int i{ }; i < items.size( ); i++ ) {
		const bool item_hovered = menu.mouse_in_rect( current_listbox->cursor_position /*- vec2_t( 0, 20 )*/, current_listbox->cursor_position + vec2_t( current_listbox->size.x, 18 ) );

		const bool is_visible = current_listbox->cursor_position.y < current_listbox->position.y + current_listbox->size.y && current_listbox->cursor_position.y > current_listbox->position.y;

		if ( item_hovered ) {
			if ( menu.mouse_active && !menu.old_mouse_active && is_visible && was_empty_last_hash ) {
				value = i;
			}
		}

		if ( value == i ) {
			menu.drawing.filled_rect( current_listbox->cursor_position + vec2_t( 1, 0 ), vec2_t( 2, 20 ), globals::menu_accent, 0.f );

			menu.drawing.multi_color_filled_rect( current_listbox->cursor_position, vec2_t( current_listbox->size.x / 2.5f, 20 ), { globals::palette::white.alpha( 20 ),  globals::palette::white.alpha( 0 ),  globals::palette::white.alpha( 0 ), globals::palette::white.alpha( 20 ) } );
		}

		auto item_text_sz = menu.drawing.calc_text_size( items.at( i ) );
		menu.drawing.text( current_listbox->cursor_position + vec2_t( 5, ( item_text_sz.y / 2 ) - 2 ), items.at( i ), value == i ? globals::palette::white : color_t( 54, 54, 54, 255 ), text_flags::text_flags_none );

		current_listbox->cursor_position.y += 20;
	}

	menu.drawing.rect( current_listbox->position + vec2_t( 0, 19 ), vec2_t( current_listbox->size.x, height + 2 ), color_t( 0, 0, 0, 255 ), 0.f );

	menu.m_current_groupbox->cursor_position.y += current_listbox->size.y;

	menu.m_current_groupbox->m_current_listbox = current_listbox;
}

void calliope::menu_t::components_t::end_listbox( ) {
	if ( !menu.m_current_groupbox )
		return;

	if ( !menu.m_current_groupbox->m_current_listbox )
		return;

	auto listbox_ctx = menu.m_current_groupbox->m_current_listbox;

	if ( ( listbox_ctx->m_item_count * 20 ) > listbox_ctx->position.y + listbox_ctx->size.y ) {
		if ( listbox_ctx->scroll_ratio == -1.f )
			listbox_ctx->scroll_ratio = 0.f;

		int scroll_height = ( listbox_ctx->size.y ) / ( ( listbox_ctx->old_cursor_position.y - listbox_ctx->position.y ) / ( listbox_ctx->size.y ) );
		int offset = ( ( listbox_ctx->size.y - 15 ) - scroll_height ) * listbox_ctx->scroll_ratio;

		menu.drawing.filled_rect( vec2_t( listbox_ctx->position.x + listbox_ctx->size.x - 6, listbox_ctx->position.y + 20 + offset ), vec2_t( 4, 3 ), color_t( 32, 32, 32, 255 ), 0.f );
		menu.drawing.filled_rect( vec2_t( listbox_ctx->position.x + listbox_ctx->size.x - 6, listbox_ctx->position.y + 20 + offset ), vec2_t( 4, scroll_height - 6 ), color_t( 32, 32, 32, 255 ), 3.f );
		menu.drawing.filled_rect( vec2_t( listbox_ctx->position.x + listbox_ctx->size.x - 6, listbox_ctx->position.y + 20 + offset ), vec2_t( 1, scroll_height - 6 ), color_t( 32, 32, 32, 255 ), 0.f );

		if ( menu.mouse_in_rect( listbox_ctx->position, listbox_ctx->position + listbox_ctx->size ) ) {
			listbox_ctx->scroll_ratio = std::clamp( listbox_ctx->scroll_ratio - menu.mouse_wheel_delta * ( 20.f / ( ( int ) listbox_ctx->old_cursor_position.y - ( int ) ( ( int ) listbox_ctx->position.y + ( int ) listbox_ctx->size.y ) ) ), 0.f, 1.f );
		}

		if ( listbox_ctx->scroll_ratio > 0.0f )
			menu.drawing.multi_color_filled_rect( listbox_ctx->position + vec2_t( 1, 20 ), vec2_t( listbox_ctx->size.x - 8, 22 ), { color_t( 8, 8, 8, 255 ), color_t( 8, 8, 8, 255 ), color_t( 8, 8, 8, 0 ), color_t( 8, 8, 8, 0 ) } );

		if ( listbox_ctx->scroll_ratio < 1.0f )
			menu.drawing.multi_color_filled_rect( listbox_ctx->position + vec2_t( 1, listbox_ctx->size.y - 19 ), vec2_t( listbox_ctx->size.x - 8, 19 ), { color_t( 8, 8, 8, 0 ), color_t( 8, 8, 8, 0 ), color_t( 8, 8, 8, 255 ), color_t( 8, 8, 8, 255 ) } );
	}
	else {
		listbox_ctx->scroll_ratio = -1.f;
	}

	listbox_ctx->scroll_ratio = std::clamp( listbox_ctx->scroll_ratio, 0.f, 1.f );

	int offset = ( int ) listbox_ctx->old_cursor_position.y - ( int ) ( ( int ) listbox_ctx->position.y + ( int ) listbox_ctx->size.y );
	listbox_ctx->cursor_position.y += !( listbox_ctx->old_cursor_position.y > ( int ) listbox_ctx->position.y + ( int ) listbox_ctx->size.y ) ? 0 : ( int ) ( offset * listbox_ctx->scroll_ratio );

	menu.drawing.pop_clip_rect( );

	listbox_ctx->old_cursor_position = listbox_ctx->cursor_position;
}
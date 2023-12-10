#include "../../calliope.hpp"

calliope::menu_t::groupbox_context_t* calliope::menu_t::components_t::groupbox( const char* title, vec2_t position, vec2_t size ) {
	auto _size = size;
	auto _position = position;

	// clamp groupbox size...
	if ( _size.x > menu.window_ctx.drawable_area.second.x )
		_size.x = menu.window_ctx.drawable_area.second.x;
	if ( _size.y > menu.window_ctx.drawable_area.second.y )
		_size.y = menu.window_ctx.drawable_area.second.y;

	auto wnd_ctx = menu.get_groupbox_by_id( Hash(title, false) );
	if ( !wnd_ctx ) {
		wnd_ctx = new calliope::menu_t::groupbox_context_t( );

		wnd_ctx->m_hash_id = Hash(title, false);
		wnd_ctx->m_id = title;
		wnd_ctx->scroll_ratio = 0.f;

		wnd_ctx->position = menu.window_ctx.drawable_area.first + _position;
		wnd_ctx->size = _size;
		wnd_ctx->cursor_position = wnd_ctx->position + vec2_t( calliope::globals::group_box_padding, calliope::globals::group_box_padding + 25 );

		menu.m_groupboxes.push_back( wnd_ctx );
	}

	wnd_ctx->position = menu.window_ctx.drawable_area.first + _position;
	wnd_ctx->size = _size;

	wnd_ctx->cursor_position = wnd_ctx->position + vec2_t( calliope::globals::group_box_padding, calliope::globals::group_box_padding + 25 );

	int offset = static_cast< int >( wnd_ctx->old_cursor_position.y ) - static_cast< int >( static_cast< int >( wnd_ctx->position.y ) + static_cast< int >( wnd_ctx->size.y ) );
	
	if ( wnd_ctx->old_cursor_position.y > wnd_ctx->position.y + wnd_ctx->size.y ) {
		wnd_ctx->cursor_position.y -= static_cast< int >( offset * wnd_ctx->scroll_ratio );
	}

	menu.drawing.multi_color_filled_rect( wnd_ctx->position + vec2_t( 1, 1 ), vec2_t( _size.x - 2, 25 ), { color_t( 16, 16, 16, 150 ), color_t( 16, 16, 16, 150 ), color_t( 8, 8, 8, 150 ), color_t( 8, 8, 8, 150 ) } );

	menu.drawing.text( wnd_ctx->position + vec2_t( 5, 6 ), title, color_t( 75, 75, 75, 255 ), text_flags::text_flags_none );

	menu.drawing.filled_rect( wnd_ctx->position + vec2_t( 1, 25 ), vec2_t( _size.x - 2, _size.y - 26 ), color_t( 8, 8, 8, 150 ), 0.f );

	menu.drawing.multi_color_filled_rect( wnd_ctx->position + vec2_t( _size.x / 2, 25 ), vec2_t( _size.x / 2, 1 ), { globals::palette::black.alpha( 0 ), color_t( 52, 52, 52, 150 ), color_t( 52, 52, 52, 150 ), globals::palette::black.alpha( 0 ) } );
	menu.drawing.multi_color_filled_rect( wnd_ctx->position + vec2_t( 0, 25 ), vec2_t( _size.x, 1 ), { color_t( 52, 52, 52, 150 ), globals::palette::black.alpha( 0 ), globals::palette::black.alpha( 0 ), color_t( 52, 52, 52, 150 ) } );

	menu.drawing.rect( wnd_ctx->position, _size, color_t( 52, 52, 52, 255 ), 3.f );

	menu.drawing.push_clip_rect( vec2_t( wnd_ctx->position.x, wnd_ctx->position.y + calliope::globals::group_box_padding + 14 ), vec2_t( wnd_ctx->position.x + wnd_ctx->size.x + 16, wnd_ctx->position.y + wnd_ctx->size.y - 1 ), true );

	menu.m_current_groupbox = wnd_ctx;
	return wnd_ctx;
}

void calliope::menu_t::components_t::end_groupbox( ) {
	auto wnd_ctx = menu.m_current_groupbox;
	if ( !wnd_ctx )
		return;

	wnd_ctx->cursor_position.y += 8;

	if ( wnd_ctx->old_cursor_position.y > wnd_ctx->position.y + wnd_ctx->size.y && ( wnd_ctx->scroll_ratio >= 0.f ) ) {
		if ( wnd_ctx->scroll_ratio == -1.f )
			wnd_ctx->scroll_ratio = 0.f;

		int scroll_height = ( wnd_ctx->size.y - 25 ) / ( ( wnd_ctx->old_cursor_position.y - wnd_ctx->position.y ) / ( wnd_ctx->size.y - 25 ) );
		int offset = ( ( wnd_ctx->size.y - 25 ) - scroll_height ) * wnd_ctx->scroll_ratio;

		//menu.drawing.filled_rect( vec2_t( wnd_ctx->position.x + wnd_ctx->size.x - ( wnd_ctx->scroll_bar_width + 1 ), wnd_ctx->position.y ), vec2_t( wnd_ctx->scroll_bar_width, wnd_ctx->size.y ), color_t( 52, 52, 52, 255 ), 3.f );
		
		if ( wnd_ctx->scroll_bar_width > 1.f ) {
			menu.drawing.filled_rect( vec2_t( wnd_ctx->position.x + wnd_ctx->size.x - ( wnd_ctx->scroll_bar_width ), wnd_ctx->position.y + 28 + offset ), vec2_t( wnd_ctx->scroll_bar_width - 2, 3 ), color_t( 32, 32, 32, 255 ), 0.f );
			menu.drawing.filled_rect( vec2_t( wnd_ctx->position.x + wnd_ctx->size.x - ( wnd_ctx->scroll_bar_width ), wnd_ctx->position.y + 28 + offset ), vec2_t( wnd_ctx->scroll_bar_width - 2, scroll_height - 6 ), color_t( 32, 32, 32, 255 ), 3.f );
			menu.drawing.filled_rect( vec2_t( wnd_ctx->position.x + wnd_ctx->size.x - ( wnd_ctx->scroll_bar_width ), wnd_ctx->position.y + 28 + offset ), vec2_t( 1, scroll_height - 6 ), color_t( 32, 32, 32, 255 ), 0.f );
		}

		wnd_ctx->scroll_bar_width = 4.f;

		if ( menu.mouse_in_rect( wnd_ctx->position, wnd_ctx->position + wnd_ctx->size ) ) {
			if ( menu.window_ctx.m_active_hash == 0 )
				wnd_ctx->scroll_ratio = std::clamp( wnd_ctx->scroll_ratio - menu.mouse_wheel_delta * ( 20.f / ( ( int ) wnd_ctx->old_cursor_position.y - ( int ) ( ( int ) wnd_ctx->position.y + ( int ) wnd_ctx->size.y ) ) ), 0.f, 1.f );

			wnd_ctx->scroll_bar_width = 6.f;//min( wnd_ctx->scroll_bar_width + 0.2f, 6.f );
		}

		if ( wnd_ctx->scroll_ratio > 0.0f )
			menu.drawing.multi_color_filled_rect( wnd_ctx->position + vec2_t( 2, 26 ), vec2_t( wnd_ctx->size.x - 4, 22 ), { color_t( 8, 8, 8, 255 ), color_t( 8, 8, 8, 255 ), color_t( 8, 8, 8, 0 ), color_t( 8, 8, 8, 0 ) } );

		if ( wnd_ctx->scroll_ratio < 1.0f )
			menu.drawing.multi_color_filled_rect( wnd_ctx->position + vec2_t( 2, wnd_ctx->size.y - 20 ), vec2_t( wnd_ctx->size.x - 4, 19 ), { color_t( 8, 8, 8, 0 ), color_t( 8, 8, 8, 0 ), color_t( 8, 8, 8, 255 ), color_t( 8, 8, 8, 255 ) } );
	}
	else {
		wnd_ctx->scroll_ratio = -1.f;
	}

	wnd_ctx->scroll_ratio = std::clamp( wnd_ctx->scroll_ratio, 0.f, 1.f );

	int offset = ( int ) wnd_ctx->old_cursor_position.y - ( int ) ( ( int ) wnd_ctx->position.y + ( int ) wnd_ctx->size.y );
	wnd_ctx->cursor_position.y += !( wnd_ctx->old_cursor_position.y > ( int ) wnd_ctx->position.y + ( int ) wnd_ctx->size.y ) ? 0 : ( int ) ( offset * wnd_ctx->scroll_ratio );
	wnd_ctx->old_cursor_position = wnd_ctx->cursor_position;

	menu.drawing.pop_clip_rect( );

	menu.m_current_groupbox = wnd_ctx;
}
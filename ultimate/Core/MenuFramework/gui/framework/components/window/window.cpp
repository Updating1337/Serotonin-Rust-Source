#include "../../calliope.hpp"
#include <vector>

static bool initialized_context;

inline calliope::menu_t calliope::menu;


bool calliope::menu_t::components_t::window( const char* title, vec2_t position, vec2_t window_size, int flags ) {
	if ( calliope::util::is_key_pressed( RustStructs::Insert ) && !( flags & window_flags::window_flags_always_open ) )
		menu.window_ctx.is_open = !menu.window_ctx.is_open;

	if ( !initialized_context ) {
		menu.window_ctx.position = position;
		menu.window_ctx.size = window_size;

		initialized_context = true;
	}

	menu.mouse_active = calliope::util::is_key_held( RustStructs::Mouse0 );

	vec2_t m_point;

	m_point.x = UnityEngine::Input::GetMousePosition().x;
	m_point.y = UnityEngine::Screen::get_height() - UnityEngine::Input::GetMousePosition().y;

	menu.mouse_pos = vec2_t(
		static_cast< float >( m_point.x ),
		static_cast< float >( m_point.y )
	);

	const auto drawing = menu.drawing;

	if ( menu.window_ctx.is_open ) {
		if ( menu.mouse_in_rect( menu.window_ctx.position, menu.window_ctx.position + vec2_t( menu.window_ctx.size.x, 18 ) ) && menu.mouse_active ) {
			menu.window_ctx.position.x += menu.mouse_pos.x - menu.old_mouse_pos.x;
			menu.window_ctx.position.y += menu.mouse_pos.y - menu.old_mouse_pos.y;
		}

		menu.window_ctx.drawable_area.first = menu.window_ctx.position + vec2_t( calliope::globals::window_padding, calliope::globals::window_padding );
		menu.window_ctx.drawable_area.second = menu.window_ctx.size - vec2_t( calliope::globals::window_padding * 2, calliope::globals::window_padding * 2 );

		drawing.filled_rect( menu.window_ctx.position, menu.window_ctx.size, color_t( 11, 11, 11, 255 ), 0.f );

		if ( menu.watermark_icon.has_value( ) ) {
			auto watermark_sz = vec2_t( 150, 150 );
			drawing.image( menu.window_ctx.position + menu.window_ctx.size - watermark_sz, watermark_sz, menu.watermark_icon.value( ) );

			drawing.filled_rect( menu.window_ctx.position, menu.window_ctx.size, color_t( 20, 20, 20, 150 ), 0.f );
		}

		if ( !( flags & window_flags::window_flags_no_titlebar ) ) {
#ifdef CALLIOPE_USE_TEXT_SIZE
			auto text_sz = menu.drawing.calc_text_size( title );
			menu.drawing.text( menu.window_ctx.position + vec2_t( menu.window_ctx.size.x - ( text_sz.x + 265 ), 2 ), title, globals::menu_accent, text_flags::text_flags_style_dropshadow );

			menu.window_ctx.drawable_area.first.y += calliope::globals::title_bar_height;
			menu.window_ctx.drawable_area.second.y -= ( calliope::globals::title_bar_height );
#else 
			calliope::drawing.filled_rect( calliope::window_ctx.position, { calliope::window_ctx.size.x, calliope::globals::title_bar_height }, color_t( 18, 18, 18, 255 ) );
			calliope::drawing.text( calliope::window_ctx.position + vec2_t( 5, 0 ), title, color_t( 255, 255, 255, 255 ), text_flags::text_flags_style_outline );
#endif // CALLIOPE_USE_TEXT_SIZE

			menu.drawing.multi_color_filled_rect( menu.window_ctx.position + vec2_t( 0, calliope::globals::title_bar_height ), { menu.window_ctx.size.x, 6 }, { color_t( 8, 8, 8, 255 ), color_t( 8, 8, 8, 255 ), globals::palette::black.alpha( 0 ), globals::palette::black.alpha( 0 ) } );
		}

#ifdef CALLIOPE_USE_TEXT_SIZE
		auto watermark_text_sz = menu.drawing.calc_text_size( "rust" );

		menu.drawing.multi_color_filled_rect( menu.window_ctx.position + vec2_t( 0, menu.window_ctx.size.y - ( watermark_text_sz.y * 2 ) + 3 ), { menu.window_ctx.size.x, 6 }, { globals::palette::black.alpha( 0 ), globals::palette::black.alpha( 0 ), color_t( 8, 8, 8, 255 ), color_t( 8, 8, 8, 255 ) } );

		menu.drawing.filled_rect( menu.window_ctx.position + vec2_t( 0, menu.window_ctx.size.y - watermark_text_sz.y - 3 ), { menu.window_ctx.size.x, watermark_text_sz.y + 2 }, color_t( 11, 11, 11, 255 ), 0.f );
		//menu.drawing.text( menu.window_ctx.position + vec2_t( 5, menu.window_ctx.size.y - watermark_text_sz.y - 3 ), "fullcontrol for overwatch 2", globals::palette::white, text_flags::text_flags_style_dropshadow );

		menu.window_ctx.drawable_area.second.y -= ( watermark_text_sz.y + 2 );
#endif
		menu.drawing.rect( menu.window_ctx.position, menu.window_ctx.size, color_t( 60, 60, 60, 255 ), 3.f );
		menu.drawing.rect( menu.window_ctx.position - vec2_t( 1, 1 ), menu.window_ctx.size + vec2_t( 2, 2 ), globals::palette::black, 3.f );
	}

	return menu.window_ctx.is_open;
}

int calliope::menu_t::components_t::tabs( std::vector< const char* > tab_names ) {
	const auto drawing = menu.drawing;

	static int selected_tab{ 0 };

	vec2_t tab_name_start = menu.window_ctx.position + vec2_t( 8, 25 );

#ifdef CALLIOPE_USE_TEXT_SIZE
	for ( int i{ }; i < tab_names.size( ); i++ ) {
		auto tab_name = tab_names.at( i );
		auto tab_name_sz = menu.drawing.calc_text_size( tab_name );

		auto tab_color = color_t( 50, 50, 50, 255 );

		const bool hovered = menu.mouse_in_rect( tab_name_start, tab_name_start + tab_name_sz );
		if ( hovered ) {
			tab_color = color_t( 150, 150, 150, 255 );

			if ( menu.mouse_active )
				selected_tab = i;
		}

		drawing.text( tab_name_start, tab_name, selected_tab == i ? globals::menu_accent : tab_color, text_flags::text_flags_style_dropshadow );
		tab_name_start.y += ( tab_name_sz.y + 10 );
	}
#endif // CALLIOPE_USE_TEXT_SIZE

	return selected_tab;
}

void calliope::menu_t::draw_list_t::text( vec2_t position, const char* text, color_t color, int flags ) {
	draw_element_t elem;

	elem.type = draw_list_t::element_type::element_type_text;
	elem.pos = position;
	elem.text = text;
	elem.colors[ 0 ] = color;
	elem.flags = flags;

	elements.push_back( elem );
}
void calliope::menu_t::draw_list_t::rect( vec2_t position, vec2_t size, color_t color, float rounding ) {
	draw_element_t elem;

	elem.type = draw_list_t::element_type::element_type_rect;
	elem.pos = position;
	elem.size = size;
	elem.colors[ 0 ] = color;
	elem.rounding = rounding;

	elements.push_back( elem );
}
void calliope::menu_t::draw_list_t::filled_rect( vec2_t position, vec2_t size, color_t color, float rounding ) {
	draw_element_t elem;

	elem.type = draw_list_t::element_type::element_type_filled_rect;
	elem.pos = position;
	elem.size = size;
	elem.colors[ 0 ] = color;
	elem.rounding = rounding;

	elements.push_back( elem );
}
void calliope::menu_t::draw_list_t::line( vec2_t start, vec2_t end, color_t color ) {
	draw_element_t elem;

	elem.type = draw_list_t::element_type::element_type_line;
	elem.pos = start;
	elem.size = end;
	elem.colors[ 0 ] = color;

	elements.push_back( elem );
}
void calliope::menu_t::draw_list_t::multi_color_filled_rect( vec2_t position, vec2_t size, std::array<color_t, 4> colors ) {
	draw_element_t elem;

	elem.type = draw_list_t::element_type::element_type_multi_color_filled_rect;
	elem.pos = position;
	elem.size = size;
	elem.colors[ 0 ] = colors[ 0 ];
	elem.colors[ 1 ] = colors[ 1 ];
	elem.colors[ 2 ] = colors[ 2 ];
	elem.colors[ 3 ] = colors[ 3 ];

	elements.push_back( elem );
}

void calliope::menu_t::draw_list_t::render_elements( ) {
	const auto drawing = menu.drawing;

	for ( draw_element_t& e : elements ) {
		switch ( e.type ) {
		case draw_list_t::element_type::element_type_filled_rect:
			drawing.filled_rect( e.pos, e.size, e.colors[ 0 ], e.rounding );
			break;
		case draw_list_t::element_type::element_type_rect:
			drawing.rect( e.pos, e.size, e.colors[ 0 ], e.rounding );
			break;
		case draw_list_t::element_type::element_type_line:
			drawing.line( e.pos, e.size, e.colors[ 0 ] ); // size is used as end point here...
			break;
		case draw_list_t::element_type::element_type_text:
			drawing.text( e.pos, e.text, e.colors[ 0 ], e.flags );
			break;
		case draw_list_t::element_type::element_type_multi_color_filled_rect:
			drawing.multi_color_filled_rect( e.pos, e.size, std::array<color_t, 4>{ e.colors[ 0 ], e.colors[ 1 ], e.colors[ 2 ], e.colors[ 3 ] } );
			break;
		default:
			break;
		}
	}

	elements.clear( );
}

void calliope::menu_t::components_t::end_window( ) {
	menu.draw_list.render_elements( );

	//menu.drawing.filled_rect( menu.mouse_pos, vec2_t( 4, 4 ), color_t( 255, 0, 0, 255 ), 0.f );

	menu.old_mouse_active = menu.mouse_active;
	menu.old_mouse_pos = menu.mouse_pos;
	menu.mouse_wheel_delta = 0.f;

	menu.window_ctx.m_last_hash = menu.window_ctx.m_active_hash;
}
#include "../../calliope.hpp"

const calliope::color_t slider_back_color( 32, 32, 32, 255 );

const calliope::color_t slider_description_color( 44, 44, 44, 255 );
const calliope::color_t slider_hovered_description_color( 160, 160, 160, 255 );

template<typename value_t>
void calliope::menu_t::components_t::slider( const char* name, const char* suffix, value_t& value, value_t min, value_t max, std::optional< component_info_t > description ) {
	const constexpr auto is_float_mode = std::is_same_v<value_t, float>;
	static std::string str_value = std::to_string( static_cast< int >( value ) );

	if ( !menu.m_current_groupbox )
		return;

	auto slider_position = menu.m_current_groupbox->cursor_position + vec2_t( 0, 18 );
	const auto slider_size = vec2_t( menu.m_current_groupbox->size.x - 54, 5 );

	menu.drawing.filled_rect( slider_position, slider_size, slider_back_color, 0.f );

	bool middle_aligned = min < static_cast< value_t >( 0 );
	bool hovered = menu.mouse_in_rect( slider_position, slider_position + slider_size );

	const bool was_empty_last_hash = menu.window_ctx.m_last_hash == 0 && menu.window_ctx.m_active_hash == 0;

	if ( hovered && ( menu.mouse_active && !menu.old_mouse_active ) && was_empty_last_hash ) {
		menu.window_ctx.m_active_hash = util::hash( name );
	}

	if ( hovered && ( menu.mouse_active && !menu.old_mouse_active ) && was_empty_last_hash && util::is_key_held( VK_CONTROL ) ) {
		menu.window_ctx.m_active_hash = util::hash( name ) + 2;
	}

	else if ( menu.window_ctx.m_active_hash == ( util::hash( name ) + 2 ) ) {
		if ( util::is_key_pressed( VK_BACK ) && str_value.size( ) > 0 ) {
			str_value.pop_back( );
		}

		if ( util::is_key_pressed( VK_ESCAPE ) || util::is_key_pressed( VK_RETURN ) || ( !hovered && menu.mouse_active ) ) {
			bool has_number = std::find_if( str_value.begin( ), str_value.end( ), myIsDigit) != str_value.end( );

			int minus_count = 0; // this is gay but works fine... lol
			for ( int idx = 0; idx < str_value.size( ); idx++ ) {
				if ( str_value.at( idx ) == '-' )
					minus_count++;
			}

			if ( has_number && minus_count < 2 && !str_value.empty( ) ) {
				if constexpr ( is_float_mode ) {
					value = std::clamp(stof_c( str_value ), static_cast< float >( min ), static_cast< float >( max ) );
				}
				else {
					value = std::clamp( static_cast< int >(stof_c( str_value ) ), static_cast< int >( min ), static_cast< int >( max ) );
				}
			}

			menu.window_ctx.m_active_hash = 0;
		}

		for ( int k{ }; k < VK_OEM_8; k++ ) {
			bool is_numeric = k >= static_cast< int >( '0' ) && k <= static_cast< int >( '9' );
			if ( !is_numeric && k != VK_OEM_PERIOD && k != VK_OEM_MINUS )
				continue;

			if ( util::is_key_pressed( k ) ) {
				if ( k == VK_OEM_MINUS ) {
					str_value += '-';
				}
				else if ( k == VK_OEM_PERIOD ) {
					str_value += '.';
				}
				else {
					str_value += static_cast< char >( k );
				}
			}
		}
	}


	else if ( menu.mouse_active && menu.window_ctx.m_active_hash == util::hash( name ) ) {
		if constexpr ( is_float_mode ) {
			value = static_cast< float >( std::clamp( menu.mouse_pos.x - slider_position.x, static_cast< float >( min ), ( ( slider_size.x ) - 1 ) ) / ( slider_size.x - 1 ) * ( max - min ) + min );
			value = static_cast< float >( std::clamp( value, static_cast< float >( min ), static_cast< float >( max ) ) );
		}
		else {
			value = static_cast< int >( std::clamp( menu.mouse_pos.x - slider_position.x, static_cast< float >( min ), ( slider_size.x - 1 ) ) / ( slider_size.x - 1 ) * ( max - min ) + min );
			value = static_cast< int >( std::clamp( value, static_cast< int >( min ), static_cast< int >( max ) ) );
		}
	}
	else if ( !menu.mouse_active && menu.window_ctx.m_active_hash == util::hash( name ) ) {
		menu.window_ctx.m_active_hash = 0;
	}

	const float rect_width = middle_aligned ? value * ( slider_size.x * 0.5f ) / max : value * ( slider_size.x ) / max;

	char buf[ 256 ];

	if constexpr ( is_float_mode )
		sprintf( buf, XS("%.2f%s"), value, suffix );
	else
		sprintf( buf, XS("%d%s"), value, suffix );

	if ( middle_aligned ) {
		menu.drawing.multi_color_filled_rect( slider_position + vec2_t( slider_size.x / 2.f, 0 ), vec2_t( rect_width, slider_size.y ), { calliope::globals::menu_accent, calliope::globals::menu_accent, calliope::globals::menu_accent.darker( 50 ), calliope::globals::menu_accent.darker( 50 ) } );
	}
	else {
		menu.drawing.multi_color_filled_rect( slider_position, vec2_t( rect_width, slider_size.y ), { calliope::globals::menu_accent, calliope::globals::menu_accent, calliope::globals::menu_accent.darker( 50 ), calliope::globals::menu_accent.darker( 50 ) } );
	}

	menu.drawing.rect( slider_position, slider_size, globals::palette::black, 0.f );

#ifdef CALLIOPE_USE_TEXT_SIZE	
	const auto value_buf_sz = menu.drawing.calc_text_size( buf );
	const auto label_text_sz = menu.drawing.calc_text_size( name );

	menu.drawing.text( slider_position - vec2_t( -2, label_text_sz.y + 0 ), name, globals::palette::white, text_flags::text_flags_none );

	if ( !( menu.window_ctx.m_active_hash == ( util::hash( name ) + 2 ) ) ) {
		menu.drawing.text( slider_position + vec2_t( slider_size.x - value_buf_sz.x, -( label_text_sz.y + 2 ) ), buf, globals::palette::white, text_flags::text_flags_none );
	}
	else {
		sprintf( buf, XS("%s"), str_value.c_str( ) );
		auto value_buf_sz = menu.drawing.calc_text_size( buf );

		menu.drawing.text( slider_position + vec2_t( slider_size.x - value_buf_sz.x, -( label_text_sz.y + 2 ) ), buf, globals::palette::white, text_flags::text_flags_none );

		// whatevr lol....
		static int blink_counter = 0;
		static bool blink = false;
		if ( blink_counter > 80 )
			blink_counter = 0;

		if ( blink_counter > 40 )
			blink = !blink;

		if ( menu.window_ctx.m_active_hash == ( util::hash( name ) + 2 ) ) {
			auto blink_cursor_sz = value_buf_sz.x > 0 ? value_buf_sz.x : 15.f;

			menu.drawing.filled_rect( slider_position + vec2_t( slider_size.x - blink_cursor_sz, -3 ), vec2_t( blink_cursor_sz, 1 ), globals::palette::white.alpha( blink ? blink_counter * 5 : blink_counter / 5 ), 0.f );
		}

		blink_counter++;
	}
#endif

	if ( description.has_value( ) ) {
		auto question_mark_sz = menu.drawing.calc_text_size(XS("(?)") );
		auto end_of_slider_position = vec2_t( slider_position.x + label_text_sz.x + 3, slider_position.y - 2 - ( question_mark_sz.y ) );

		const bool hovered = menu.mouse_in_rect( end_of_slider_position, end_of_slider_position + question_mark_sz );

		menu.drawing.text( end_of_slider_position, XS("(?)"), hovered ? slider_hovered_description_color : slider_description_color, text_flags::text_flags_style_dropshadow );

		if ( hovered && menu.window_ctx.m_active_hash == 0 ) {
			auto overlay_window_position = end_of_slider_position + question_mark_sz;

			auto overlay_window_size = menu.drawing.calc_text_size( description.value( ).description ) + vec2_t( 8, 8 );

			menu.draw_list.filled_rect( overlay_window_position, overlay_window_size, color_t( 8, 8, 8, 255 ), 3.f );

			menu.draw_list.text( overlay_window_position + vec2_t( 4, 4 ), description.value( ).description, globals::palette::white, text_flags::text_flags_style_dropshadow );

			menu.draw_list.rect( overlay_window_position + vec2_t( 1, 1 ), overlay_window_size - vec2_t( 2, 2 ), color_t( 32, 32, 32, 255 ), 3.f );
			menu.draw_list.rect( overlay_window_position, overlay_window_size, globals::palette::black, 3.f );
		}
	}

	menu.m_current_groupbox->cursor_position.y += ( slider_size.y * 3.f ) + 10;
}

template void calliope::menu_t::components_t::slider( const char* name, const char* suffix, float& value, float min, float max, std::optional< component_info_t > description );
template void calliope::menu_t::components_t::slider( const char* name, const char* suffix, int& value, int min, int max, std::optional< component_info_t > description );
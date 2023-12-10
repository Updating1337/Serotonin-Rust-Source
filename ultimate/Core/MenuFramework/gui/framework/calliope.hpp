// calliope menu framework - made with love, clowie (2023)
// 

#pragma once
#include <array>
#include <algorithm>
#include <memory>
#include <functional>
#include <optional>
#include <string>
#include <set>
#include <windows.h>
#include <math.h>
#include <bcrypt.h>
#include <cmath>
#include "../../../CRT/crt.hpp"
#include "../../../SDK/UnityEngine/UnityEngine.hpp"
#include "../../../SDK/AssemblyCSharp/AssemblyCSharp.hpp"
#include "../../../Utils/xorstr.hpp"
#define CALLIOPE_INLINE __forceinline

// configuration settings
// CALLIOPE_USE_TEXT_SIZE if defined calliope will use a prototype "calc_text_size" function for centering text.
// this should be enabled if you wish to use center or right aligned text
#define CALLIOPE_USE_TEXT_SIZE 1

namespace calliope {
	// just used to store hsv colors...
	struct vec3_t {
		float x, y, z;

		vec3_t( ) : x( 0.f ), y( 0.f ), z( 0.f ) { }
		vec3_t( float x, float y, float z ) : x( x ), y( y ), z( z ) { }
	};

	struct vec2_t {
		float x, y;

		vec2_t( ) : x( 0.f ), y( 0.f ) { }
		vec2_t( float x, float y ) : x( x ), y( y ) { }

		vec2_t operator+( const vec2_t& v ) { return vec2_t( x + v.x, y + v.y ); }
		vec2_t operator-( const vec2_t& v ) { return vec2_t( x - v.x, y - v.y ); }

		vec2_t operator*( float num ) { return vec2_t( x * num, y * num ); }
		vec2_t operator/( float num ) { return vec2_t( x / num, y / num ); }

		vec2_t operator+=( const vec2_t& v ) { return vec2_t( x += v.x, y += v.y ); }

		bool operator==( float num ) { return x == num && y == num; }
	};


	using AREA = struct SArea_t
	{
		int m_iLeft, m_iTop, m_iRight, m_iBottom;
	};


	struct color_t {
		float r, g, b, a;

		color_t( int r, int g, int b ) : r( r / 255.f ), g( g / 255.f ), b( b / 255.f ), a( 1.f ) { }
		color_t( int r, int g, int b, int a ) : r( r / 255.f ), g( g / 255.f ), b( b / 255.f ), a( a / 255.f ) { }
		color_t( float r, float g, float b, float a ) : r( r ), g( g ), b( b ), a( a ) { }
		color_t( float r, float g, float b ) : r( r ), g( g ), b( b ), a( 1.f ) { }

		color_t( ) : r( 0.f ), g( 0.f ), b( 0.f ), a( 0.f ) { }

		// returns same color with modified alpha
		const color_t alpha( int value ) {
			return color_t(
				static_cast< int >( r * 255 ),
				static_cast< int >( g * 255 ),
				static_cast< int >( b * 255 ),
				value
			);
		}

		const color_t darker( int amount = 20 ) {
			return color_t(
				static_cast< int >( r * 255 ) - amount,
				static_cast< int >( g * 255 ) - amount,
				static_cast< int >( b * 255 ) - amount,
				static_cast< int >( a * 255 )
			);
		}

		const color_t lighter( int amount = 20 ) {
			return color_t( 
				static_cast< int >( r * 255 ) + amount, 
				static_cast< int >( g * 255 ) + amount, 
				static_cast< int >( b * 255 ) + amount, 
				static_cast< int >( a * 255 ) 
			);
		}

		vec3_t to_hsv( ) {
			auto swap_float = [ ]( float& a, float& b ) {
				float tmp = a;
				a = b;
				b = tmp;
			};

			float k = 0.f;
			if ( g < b ) {
				swap_float( g, b );
				k = -1.f;
			}
			if ( r < g ) {
				swap_float( r, g );
				k = -2.f / 6.f - k;
			}

			const float chroma = r - ( g < b ? g : b );
			return vec3_t( std::fabsf( k + ( g - b ) / ( 6.f * chroma + 1e-20f ) ), chroma / ( r + 1e-20f ), r );
		}
		
		static color_t hsv( float h, float s, float v, float a = 1.f ) {
			float r, g, b;

			auto hsv_to_rgb = [ ]( float h, float s, float v, float& out_r, float& out_g, float& out_b ) {
				if ( s == 0.0f ) {
					// gray
					out_r = out_g = out_b = v;
					return;
				}

				h = Math::fmodf( h, 1.0f ) / ( 60.0f / 360.0f );
				int   i = ( int ) h;
				float f = h - ( float ) i;
				float p = v * ( 1.0f - s );
				float q = v * ( 1.0f - s * f );
				float t = v * ( 1.0f - s * ( 1.0f - f ) );

				switch ( i ) {
				case 0: out_r = v; out_g = t; out_b = p; break;
				case 1: out_r = q; out_g = v; out_b = p; break;
				case 2: out_r = p; out_g = v; out_b = t; break;
				case 3: out_r = p; out_g = q; out_b = v; break;
				case 4: out_r = t; out_g = p; out_b = v; break;
				case 5: default: out_r = v; out_g = p; out_b = q; break;
				}
			};

			hsv_to_rgb( h, s, v, r, g, b );
			return color_t( r, g, b, a );
		}
	};

	namespace globals {
		constexpr int title_bar_height{ 18 };
		constexpr int group_box_padding{ 12 };
		constexpr int window_padding{ 8 };

		extern int menu_alpha;

		namespace palette {



			inline color_t black( 0, 0, 0, menu_alpha );
			inline color_t white( 255, 255, 255, menu_alpha );
		}

		extern color_t menu_accent;
	} // globals

	namespace util {
		// call at the beginning of each frame...
		// easily swappable for another key listener
		inline bool key_state[329];
		inline bool prev_key_state[329];

		inline void get_key_states() {
			for (int i{ 0 }; i < 329; i++) {
				prev_key_state[i] = key_state[i];
				key_state[i] = UnityEngine::Input::GetKey((RustStructs::KeyCode)i);
			}
		}

		inline bool is_key_pressed(int key_code) {
			return key_state[key_code] && !prev_key_state[key_code]; //GetAsyncKeyState( key_code ) & 1;
		}

		inline bool is_key_held(int key_code) {
			return key_state[key_code];
		}

		using hash_t = uint64_t;

		// can change this out or whatever...
		template<typename def>
		CALLIOPE_INLINE inline hash_t hash( def x ) {
			return Hash_C(x, false);
			//return Hash<def>{ }( x );
		}
	} // util

	class menu_t {
	public:
		vec2_t mouse_pos, old_mouse_pos /*, old_last_cursor_pos, last_cursor_pos*, last_groupbox_position, last_groupbox_size*/;
		bool mouse_active, old_mouse_active;
		
		vec2_t debug_wnd_pos;

		int menu_alpha;

		float mouse_wheel_delta, scroll_ratio;

		CALLIOPE_INLINE bool mouse_in_rect( vec2_t pos1, vec2_t pos2 ) {
			if ( old_mouse_pos.x < pos1.x || old_mouse_pos.y < pos1.y )
				return false;

			if ( old_mouse_pos.x > pos2.x || old_mouse_pos.y > pos2.y )
				return false;

			return true;
		}

		struct drawing_prototypes_t {
			void( *line )( vec2_t start, vec2_t end, color_t color );
			void( *rect )( vec2_t position, vec2_t size, color_t color, float rounding );
			void( *filled_rect )( vec2_t position, vec2_t size, color_t color, float rounding );
			void( *text )( vec2_t position, const char* text, color_t color, int flags );
#ifdef CALLIOPE_USE_TEXT_SIZE
			vec2_t( *calc_text_size )( const char* text );
#endif
			void( *image )( vec2_t position, vec2_t size, void* source );
			void( *multi_color_filled_rect )( vec2_t position, vec2_t size, std::array<color_t, 4> colors );
			void( *push_clip_rect )( vec2_t mins, vec2_t maxs, bool allow_intersections );
			void( *pop_clip_rect )( );
			float( *get_frame_time )( );
		} drawing;

		// @note : clowie - todo, replace for virtual elements with a "render" method the properties can be all in their own shit etc...
		struct draw_list_t {
			enum element_type {
				element_type_rect = 0,
				element_type_filled_rect = 1,
				element_type_line = 2,
				element_type_text = 3,
				element_type_multi_color_filled_rect = 4,
			};

			struct draw_element_t {
				int type, flags;

				float rounding;

				vec2_t pos, size;
				color_t colors[ 4 ];

				const char* text;

				draw_element_t( ) = default;
			};

			std::vector< draw_element_t > elements;

			inline void text( vec2_t position, const char* text, color_t color, int flags );
			inline void rect( vec2_t position, vec2_t size, color_t color, float rounding = 0.f );
			inline void filled_rect( vec2_t position, vec2_t size, color_t color, float rounding = 0.f );
			inline void line( vec2_t start, vec2_t end, color_t color );
			inline void multi_color_filled_rect( vec2_t position, vec2_t size, std::array<color_t, 4> colors );

			inline void render_elements( );
		} draw_list;

		struct window_context_t {
			vec2_t position, size;
			
			std::pair< vec2_t, vec2_t > drawable_area; 
			
			bool is_open{ true };
			float m_window_alpha;

			util::hash_t m_active_hash, m_last_hash; // checking hash for last frame prevents click-through element bug...
		} window_ctx;

		// listboxes and groupboxes function quite similarly... maybe there is a more global solution?
		// idk and i dont really care :{ }
		// i guess i could just merge the structs?

		struct listbox_context_t {
			vec2_t position{ }, size{ };
			vec2_t cursor_position{ }, old_cursor_position{ };

			float scroll_ratio{ };
			
			const char* m_id;
			uint64_t m_hash_id;

			int m_item_count;
		};

		struct groupbox_context_t {
			vec2_t position{ }, size{ };
			vec2_t cursor_position{ }, old_cursor_position{ };

			float scroll_ratio{ };
			float scroll_bar_width{ }, old_scroll_bar_width{ };

			const char* m_id;
			uint64_t m_hash_id;

			listbox_context_t* m_current_listbox;
			std::vector< listbox_context_t* > m_listboxes;

			listbox_context_t* get_listbox_by_id(uint64_t name) {
				for (auto& listbox : m_listboxes) {
					if (listbox->m_hash_id == name)
					{
						return listbox;
					}
				}

				return nullptr;
			}

			listbox_context_t* get_listbox_by_name( const char* name ) {
				for ( auto& listbox : m_listboxes ) {
					if ( !strcmp( listbox->m_id, name ) )
						return listbox;
				}

				return nullptr;
			}
		};

		groupbox_context_t* m_current_groupbox;

		std::vector < groupbox_context_t* > m_groupboxes;

		CALLIOPE_INLINE groupbox_context_t* get_groupbox_by_name( const char* name ) {
			for ( auto& groupbox : m_groupboxes ) {
				if ( !strcmp( groupbox->m_id, name ) )
					return groupbox;
			}

			return nullptr;
		}

		CALLIOPE_INLINE groupbox_context_t* get_groupbox_by_id(uint64_t name) {
			for (auto& groupbox : m_groupboxes) {
				if (groupbox->m_hash_id == name)
				{
					return groupbox;
				}
			}

			return nullptr;
		}

		std::optional< void* > watermark_icon;

		enum text_flags {
			text_flags_none = 0,
#ifdef CALLIOPE_USE_TEXT_SIZE
			text_flags_align_center = 1 << 0,
			text_flags_align_right = 1 << 1,
			text_flags_style_dropshadow = 1 << 2,
			text_flags_style_outline = 1 << 3,
#else
			text_flags_style_dropshadow = 1 << 0,
			text_flags_style_outline = 1 << 1,
#endif // CALLIOPE_USE_TEXT_SIZE
		};

		enum dialog_flags {
			dialog_flags_ok = 0,
			dialog_flags_yes_no = 1 << 0,
			dialog_flags_ok_cancel = 1 << 1,
		};

		enum text_input_flags {
			text_input_flags_none = 0,
			text_input_flags_allow_negatives = 1 << 0,
		};

		struct components_t {
			struct component_info_t {
				const char* description;

				component_info_t( ) = default;
				component_info_t( const char* x ) : description( x ) { }
			};

			inline bool window( const char* title, vec2_t position, vec2_t window_size, int flags = 0 );
			inline void end_window( );

			inline int tabs( std::vector< const char* > tab_names );
			
			// @note : clowie - i would like to auto size groupboxes but the system right now will suffice...
			inline groupbox_context_t* groupbox( const char* title, vec2_t position, vec2_t size );
			inline void end_groupbox( );

			inline void colorpicker( const char* title, color_t& color, bool inlined = false );

			template< typename value_t > 
			inline void slider( const char* name, const char* suffix, value_t& value, value_t min, value_t max, std::optional< component_info_t > description = std::nullopt );
			inline void button( const char* name, void(*callback)());
			inline void checkbox( const char* name, bool& value, std::optional< component_info_t > description = std::nullopt );

			inline void textbox( const char* name, std::string& value, const int max_length );

			inline void keybind( const char* name, int& key, bool inlined = false );

			inline void multi_dropdown( const char* name, std::vector< const char* > items, std::vector< bool >& values );
			inline void dropdown( const char* name, std::vector< const char* > items, int& value );
			inline void sidecombo(const char* name, std::vector<const char*> items, int& selected, vec2_t position, vec2_t size);

			inline void begin_listbox( const char* name, std::vector< const char* >& items, int& value, float vertical_spacing );
			inline void end_listbox( );

		} components;

		enum window_flags {
			window_flags_none = 0,
			window_flags_no_titlebar = 1 << 0,
			window_flags_always_open = 1 << 1,
		};
	}; // menu_t

	extern menu_t menu;
} // calliope

inline bool myIsDigit(char c) {
	return c >= '0' && c <= '9';
}

inline bool myIsSpace(char c) {
	return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}


inline float strtof(const char* nptr, char** endptr) {
	while (myIsSpace(*nptr)) {
		nptr++;
	}

	bool negative = false;
	if (*nptr == '-') {
		negative = true;
		nptr++;
	}
	else if (*nptr == '+') {
		nptr++;
	}

	float result = 0.0f;
	while (myIsDigit(*nptr)) {
		result = result * 10.0f + (*nptr - '0');
		nptr++;
	}

	if (*nptr == '.') {
		float fraction = 0.0f;
		float pow10 = 1.0f;
		nptr++;
		while (myIsDigit(*nptr)) {
			fraction = fraction * 10.0f + (*nptr - '0');
			pow10 *= 10.0f;
			nptr++;
		}
		result += fraction / pow10;
	}

	if (endptr != nullptr) {
		*endptr = const_cast<char*>(nptr);
	}

	return negative ? -result : result;
}

inline int stoi_c(const std::string& str, size_t* idx = 0, int base = 10) {
	size_t i = 0;
	while (myIsSpace(str[i])) {
		i++;
	}

	int sign = 1;
	if (str[i] == '-') {
		sign = -1;
		i++;
	}
	else if (str[i] == '+') {
		i++;
	}

	int result = 0;
	while (myIsDigit(str[i])) {
		int digit = str[i] - '0';
		if (base == 10) {
			if (result > (INT_MAX - digit) / 10) {
				// Handle overflow
				if (idx) *idx = i;
				return sign == 1 ? INT_MAX : INT_MIN;
			}
			result = 10 * result + digit;
		}
		else if (base == 16) {
			result = 16 * result + digit;
		}
		else {
			// Handle other bases if necessary
			// Not implemented in this version
		}
		i++;
	}

	if (idx) *idx = i;
	return sign * result;
}

inline float stof_c(const std::string& str) {
	const char* cstr = str.c_str();
	char* end;
	float result = strtof(cstr, &end);
	if (end == cstr) {
		// No conversion was performed, return 0.0 or handle the error as needed.
		return 0.0f;
	}
	return result;
}
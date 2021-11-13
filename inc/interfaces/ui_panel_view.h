#ifndef UI_PANEL_VIEW_H
#define UI_PANEL_VIEW_H

#include <string>

class UIPanelView {
public:
	virtual void set_marker_texture(const std::string& texture) =0;
	virtual void add_button(float x, float y, const std::string& texture,
		const std::string& text, const std::string& font,
							size_t charsize) =0;
	virtual void set_button_label(size_t btn_num, const std::string& text,
				const std::string& font, size_t charsize) =0;
	virtual void add_label(float x, float y, const std::string& text,
				const std::string& font, size_t charsize) =0;
	virtual void set_active_button(size_t btn_num) =0;
	virtual ~UIPanelView() =default;
};

#endif

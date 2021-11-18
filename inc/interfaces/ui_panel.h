#ifndef UI_PANEL_H
#define UI_PANEL_H

#include <string>
#include <memory>
#include "ui_button.h"

class UIPanel {
public:
	virtual void select_prev_button() =0;
	virtual void select_next_button() =0;
	virtual void click_button() =0;
	virtual void notify(const std::string& event) =0;
	virtual ~UIPanel() =default;
};

#endif

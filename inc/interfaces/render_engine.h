#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <memory>
#include "cell_element.h"
#include "action_listener.h"
#include "ui_panel_view.h"

class Field;

class RenderEngine : public ActionListener {
public:
	virtual void render_frame() =0;
	virtual void register_field(const Field& f) =0;
	virtual void register_cell(Point2D pos,
					const std::string& res) =0;
	virtual void register_cell_element(const CellElement& el,
				const std::string& res) =0;
	virtual std::unique_ptr<UIPanelView> register_panel(
				const std::string& texture) =0;
	virtual void pop_panel() =0;
	virtual void clear_field() =0;
	virtual ~RenderEngine() =default;
};

#endif

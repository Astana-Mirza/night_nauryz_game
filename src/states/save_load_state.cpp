#include "../../inc/states/save_load_state.h"

SaveLoadState::SaveLoadState(Game& g, const std::shared_ptr<Visitor>& sv):
				PanelState::PanelState(g), saver{sv} {
	panel = std::make_unique<SaveLoadPanel>(*(game.get_painter()), *this);
}


void SaveLoadState::save_or_load(const std::string& filename) {
	if (saver) {
		try {
			saver->save_field(filename);
			close();
		} catch(FileError& e) {
			auto info = std::make_unique<InfoState>(game,
					"File error: " + e.what() +
					'\n' + e.get_filename());
			game.push_state(std::move(info));
		} catch(WallError& e) {
			auto info = std::make_unique<InfoState>(game,
					"Wall error: " + e.what() + '\n');
			game.push_state(std::move(info));
		} catch(GameError& e) {
			auto info = std::make_unique<InfoState>(game,
					"Game error: " + e.what() + '\n');
			game.push_state(std::move(info));
		}
	} else {
		StandardBuilder builder{game};
		if (builder.load(filename)) {
			game.get_painter()->clear();
			game.get_painter()->apply_preload();
			game.push_state(builder.get_result(), true);
		}
	}
}

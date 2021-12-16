#ifndef FIELD_BUILDER_H
#define FIELD_BUILDER_H

#include "igameplay_manager.h"
#include "../field.h"

class FieldBuilder {
public:
	virtual void reset(const std::string& saved_level) =0;
	virtual void setup_cells() =0;
	virtual void spawn_elements() =0;
	virtual Field&& get_result() =0;
	virtual ~FieldBuilder() =default;
};

#endif

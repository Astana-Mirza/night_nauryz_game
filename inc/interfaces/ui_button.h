#ifndef UI_BUTTON_H
#define UI_BUTTON_H

class UIButton {
public:
	virtual void click() =0;
	virtual ~UIButton() =default;
};

#endif

#pragma once

#define CREATE_FIELD(cName) class cName : public Field { \
							public: \
								virtual void initField(); \
								virtual void changedField(); \
								CREATE_FUNC(cName); 

#define FONT_NAME "fonts/font_1_honokamarugo_1.1.ttf"
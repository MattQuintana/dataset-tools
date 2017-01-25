/*
 * wmain.h
 *
 *  Created on: 25/01/2017
 *      Author: john
 */

#ifndef WMAIN_H_
#define WMAIN_H_

#include <QtWidgets>
#include "ui_wmain.h"

/**
 * Page to select the tool
 */
class wmain : public QWidget {
	Q_OBJECT
public:
	wmain(QWidget* parent = 0);
	virtual ~wmain();

private:
	Ui::DatasetTool *ui;
};

#endif /* WMAIN_H_ */

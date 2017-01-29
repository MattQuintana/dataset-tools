/*
 * labelToolPage.h
 *
 *  Created on: 28/01/2017
 *      Author: john
 */

#ifndef LABELTOOLPAGE_H_
#define LABELTOOLPAGE_H_

#include "ui_labelToolPage.h"
#include "gui/gui.h"
#include <QWidget>
#include <QProcess>
#include <QStringList>
#include <QFileDialog>

class labelToolPage : public QWidget{
	Q_OBJECT
public:
	labelToolPage(QWidget *parent = 0);
	virtual ~labelToolPage();

public slots:
	//Button event to return main page
	void goMainPage();
	//Button event to label scene
	void labelDataset();
	//Button event to select dataset
	void setDataset();
	//Button event to select output
	void setOutput();

private:
	Ui::labelToolPage *mUi;
	QProcess *mLabelToolProcess;

	QString mLastDataset;
	QString mLastOutput;

	static const QString KINPUTFORMATS;
	static const QString KOUTPUTIMAGEFORMATS;
};

#endif /* LABELTOOLPAGE_H_ */

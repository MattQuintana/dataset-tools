/*
 * labelToolPage.cpp
 *
 *  Created on: 28/01/2017
 *      Author: john
 */

#include <gui/pages/labelToolPage.h>

const QString labelToolPage::KIMAGEFORMATS = tr("Images (*.png )");
const QString labelToolPage::KINPUTFORMATS = tr("Images (*.csv *.txt)");
const QString labelToolPage::KOUTPUTIMAGEFORMATS = tr("Images (*.png)");

labelToolPage::labelToolPage(QWidget *parent) :
QWidget(parent),
mUi(new Ui::labelToolPage){
	mUi->setupUi(this);
	mLabelToolProcess = new QProcess(this);
	connect(mUi->pbReturnMainPage, SIGNAL(clicked()), this, SLOT(goMainPage()));
	connect(mUi->pbSetDataset, SIGNAL(clicked()), this, SLOT(setDataset()));
	connect(mUi->pbSetOutput, SIGNAL(clicked()), this, SLOT(setOutput()));
	connect(mUi->pbExecute, SIGNAL(clicked()), this, SLOT(labelDataset()));
	connect(mLabelToolProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readyOutputMsgProcess()));
	connect(mUi->pbAddMask, SIGNAL(clicked()), this, SLOT(addMask()));
}

void labelToolPage::setDataset(){
	QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open File"),
			mLastDataset.toLocal8Bit().constData(),
			KINPUTFORMATS);
	if(!fileName.isNull()){
		mLastDataset = fileName;
		mUi->txtDataset->setText(fileName);
	}
}

void labelToolPage::setOutput(){
	QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open File"),
			mLastOutput.toLocal8Bit().constData(),
			KOUTPUTIMAGEFORMATS);
	if(!fileName.isNull()){
		mLastOutput = fileName;
		mUi->txtOutput->setText(fileName);
	}
}

void labelToolPage::readyOutputMsgProcess(){
	QString s = tr(mLabelToolProcess->readAllStandardOutput());
	mUi->txtOutputProcess->appendPlainText(s);
}

void labelToolPage::goMainPage(){
	gui::goToPage("mainPage");
}

labelToolPage::~labelToolPage() {
	delete mUi;
}

void labelToolPage::addMask(){
	QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open File"),
			mLastMask.toLocal8Bit().constData(),
			KIMAGEFORMATS);
	if(!fileName.isNull()){
		mLastMask = fileName;
	}

	mUi->listAddedMasks->addItem(fileName);
}

void labelToolPage::labelDataset(){
	QStringList arguments;
	arguments << QDir::currentPath() + QDir::separator() + "indexPngDataset.py";
	arguments << mUi->txtDataset->text();
	arguments << mUi->txtOutput->text();
	for(int i=0; i<mUi->listAddedMasks->count(); ++i){
		arguments << mUi->listAddedMasks->item(i)->text();
	}

	if(mLabelToolProcess->isOpen()){
		mLabelToolProcess->kill();
		mLabelToolProcess->waitForFinished();
	}

	mLabelToolProcess->start("python", arguments);
}


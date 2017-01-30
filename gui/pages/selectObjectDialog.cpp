/*
 * selectObjectDialog.cpp
 *
 *  Created on: 30/01/2017
 *      Author: john
 */

#include <gui/pages/selectObjectDialog.h>

const char selectObjectDialog::KSEPARATOR = ';';

selectObjectDialog::selectObjectDialog(){
	//setParent(parent);
	mVerticalLayout = new QVBoxLayout(this);
	mDatasetList = new QListWidget(this);
	mVerticalLayout->addWidget(mDatasetList);
}

void selectObjectDialog::loadDataset(const QString& filePath){
	std::ifstream ifs(filePath.toLocal8Bit().constData());
	std::string line="";
	QString name="";
	bool getted = false;

	if(ifs.is_open()){
		getline(ifs, line);
		while(line.length() != 0 && !ifs.eof()){
			for(int i=0; i<line.length() && !getted; ++i){
				if(line[i] != KSEPARATOR)
					name.append(line[i]);
				else
					getted = true;
			}
			mDatasetList->addItem(name);
			name.clear();
			getted = false;
			getline(ifs, line);
		}
	}
}

selectObjectDialog::~selectObjectDialog() {
}


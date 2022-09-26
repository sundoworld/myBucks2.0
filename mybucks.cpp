#include <QtGui> 
#include "mybucks.h"

// if we include <QtGui> there is no need to include every class used: <QString>, <QFileDialog>,...

myBucks::myBucks(QMainWindow *parent)
        :QMainWindow(parent)
{
	setupUi( this ); // this sets up GUI
	
	//To remove Maximize option on right top of the window
	Qt::WindowFlags flags;
	flags = Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint;
	setWindowFlags( flags );
	setWindowIcon(QIcon("icon.png"));

	//To start the app in the centre of the screen
	QDesktopWidget *desktop = QApplication::desktop();

	int screenWidth, width; 
	int screenHeight, height;
	int x, y;
	QSize windowSize;
	 
	screenWidth = desktop->width(); // get width of screen
	screenHeight = desktop->height(); // get height of screen
	 
	windowSize = size(); // size of our application window
	width = windowSize.width(); 
	height = windowSize.height();
	x = (screenWidth - width) / 2;   // little computations to find centre
	y = (screenHeight - height) / 2;
	y -= 50;
	move ( x, y );  // move window to centre
	
	//Add Menu Bar Items here
        QAction *about = new QAction("&About", this);
	QAction *info = new QAction("&Information", this);
	QAction *grtotal = new QAction("&Grand Total", this);
        QMenu *file;
	file = menuBar()->addMenu("&Help");
	file->addAction(info);
	file->addAction(grtotal);
	file->addAction(about);
	
	//Update the current_balances to app
        get();
	QString db = QString::fromUtf8(value[0].c_str());
        QString sbi = QString::fromUtf8(value[1].c_str());
        QString icici = QString::fromUtf8(value[2].c_str());
	QString wallet = QString::fromUtf8(value[3].c_str());
        lineEdit->setDisabled(1);
        lineEdit_2->setDisabled(1);
        lineEdit_3->setDisabled(1);
        lineEdit_4->setDisabled(1);
	lineEdit->setText( db );
	lineEdit_2->setText( sbi );
	lineEdit_3->setText( icici );
	lineEdit_4->setText( wallet );
	
	
	//To Check for initial time file availability
	QFile fileee("monthly_expenses.csv");
     	if (!fileee.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QFile firstout("monthly_expenses.csv");
		if( !firstout.open(QIODevice::WriteOnly) ) {
		      QMessageBox::about(this, "File Write Error",
			"Unable to Write data into File: \n1. Either no space in HDD.\n2. Or no permission for current user to save file.\nContact System Admin");
		} else {
		      QTextStream fireout(&firstout);
		      balancee = 0.0;
		      balancee = balancee + (double)atof(value[0].c_str());
		      fireout << "DATE,PAY BY,PARTICULARS,DEBIT,CREDIT,BALANCE,OFF-NET\n" << currentDateTime() <<",DB AG,Month Start,,"<< db << "," << QString::number(balancee) << ",-"<< endl;
		      balancee = balancee + (double)atof(value[1].c_str());
		      fireout << currentDateTime() <<",SBI,Month Start,,"<< sbi << "," << QString::number(balancee) << ",-"<< endl;
		      balancee = balancee + (double)atof(value[2].c_str());
		      fireout << currentDateTime() <<",ICICI,Month Start,,"<< icici << "," << QString::number(balancee) << ",-"<< endl;
		      balancee = balancee + (double)atof(value[3].c_str());
		      fireout << currentDateTime() <<",CASH,Month Start,,"<< wallet << "," << QString::number(balancee) << ",-"<< endl;
		}
		QMessageBox::about(this, "File Operation",
                                 "monthly_expenses.csv file not found, its created now...");
		QFile balout("current_balances.csv");
		if( !balout.open(QIODevice::WriteOnly) ) {
		    QMessageBox::about(this, "File Write Error",
			"Unable to Write data into File: \n1. Either no space in HDD.\n2. Or no permission for current user to save file.\nContact System Admin");
		} else {
		    QTextStream fwout(&balout);
		    fwout << "DB," << db << endl << "SBI," << sbi << endl << "ICICI," << icici << endl << "WALLET," << wallet << endl << "BALANCE," << QString::number(balancee) << endl << "EOF,999999";
		}
	}
	

	// signals/slots mechanism in action
	connect( pushButton, SIGNAL( clicked() ), this, SLOT( myBucksTrack() ) );
	connect( about, SIGNAL( triggered() ), this , SLOT( about() ) ); 
	connect( info, SIGNAL( triggered() ), this , SLOT( info() ) );
	connect( grtotal, SIGNAL( triggered() ), this , SLOT( gtotal() ) );
	connect( comboBox_2, SIGNAL( currentIndexChanged( int ) ), this, SLOT( handleSelectionChanged( int ) ));
}


void myBucks::myBucksTrack()
{
	QString buf, db_new, sbi_new, icici_new, wallet_new, balance_new, new_bee, bal_new_atm;
	double bal = 0.0, new_value = 0.0;
	buf.append(currentDateTime());
	buf.append(",");
	buf.append(comboBox->currentText());
	buf.append(",");
	buf.append(lineEdit_5->text());
	buf.append(",");
	if(comboBox_2->currentIndex()==0) { //debit[-]
		buf.append(lineEdit_6->text());
		buf.append(",");
		buf.append(",");
		bal = (double)atof(value[4].c_str()) - lineEdit_6->text().toDouble();
		buf.append(QString::number(bal));
		new_bee = QString::number((double)atof(value[comboBox->currentIndex()].c_str()) - lineEdit_6->text().toDouble());
	}else if(comboBox_2->currentIndex()==1) { //credit[+]
		buf.append(",");
		buf.append(lineEdit_6->text());
		buf.append(",");
		bal = (double)atof(value[4].c_str()) + lineEdit_6->text().toDouble();
		buf.append(QString::number(bal));
		new_bee = QString::number((double)atof(value[comboBox->currentIndex()].c_str()) + lineEdit_6->text().toDouble());
	}
	if( checkBox_2->checkState() == Qt::Checked ) {
		buf.append(",");
		buf.append("*");
	}else if( checkBox_2->checkState() == Qt::Unchecked ) {
		buf.append(",");
		buf.append("-");
	}
	buf.append("\n");
	balance_new = QString::number(bal);
	
	switch(comboBox->currentIndex()) { 
		case 0:				//Deutsche Bank
                        db_new = new_bee;
			sbi_new = QString::fromUtf8(value[1].c_str());
			icici_new = QString::fromUtf8(value[2].c_str());
			wallet_new = QString::fromUtf8(value[3].c_str());
			break;
                case 1:				//State Bank of India
			db_new = QString::fromUtf8(value[0].c_str());
                	sbi_new = new_bee;
			icici_new = QString::fromUtf8(value[2].c_str());
			wallet_new = QString::fromUtf8(value[3].c_str());
			break;
                case 2:				//ICICI Bank
			db_new = QString::fromUtf8(value[0].c_str());
			sbi_new = QString::fromUtf8(value[1].c_str());
			icici_new = new_bee;
                        wallet_new = QString::fromUtf8(value[3].c_str());
			break;
		case 3:                         //Cash from Wallet
			db_new = QString::fromUtf8(value[0].c_str());
			sbi_new = QString::fromUtf8(value[1].c_str());
			icici_new = QString::fromUtf8(value[2].c_str());
                        wallet_new = new_bee;
			break;
	}
	
	if( checkBox->checkState() == Qt::Checked ) {
		new_value = (double)atof(value[3].c_str()) + lineEdit_6->text().toDouble();
		wallet_new = QString::number(new_value);
	}

///////////////////////////////////////
	QFile bankout("monthly_expenses.csv");
	if( !bankout.open(QIODevice::Append) ) {
		QMessageBox::about(this, "File Write Error",
                                   "Unable to Write data into File. Contact System Admin");
	} else {
		QTextStream fout(&bankout);
		fout << buf;
		if( checkBox->checkState() == Qt::Checked ) {
			new_value = bal + lineEdit_6->text().toDouble();
			bal_new_atm = QString::number(new_value);
			fout << currentDateTime() <<","<<"CASH,Wallet Withdraw,,"<< lineEdit_6->text() << "," << bal_new_atm << ",-"<< endl;
		}
	}
	QFile balout("current_balances.csv");
	if( !balout.open(QIODevice::WriteOnly) ) {
		QMessageBox::about(this, "File Write Error",
			"Unable to Write data into File: \n1. Either no space in HDD.\n2. Or no permission for current user to save file.\nContact System Admin");
	} else {
		QTextStream fwout(&balout);
		if( checkBox->checkState() == Qt::Checked ) {
			fwout << "DB," << db_new << endl << "SBI," << sbi_new << endl << "ICICI," << icici_new << endl << "WALLET," << wallet_new << endl << "BALANCE," << bal_new_atm << endl << "EOF,999999";
		} else {
			fwout << "DB," << db_new << endl << "SBI," << sbi_new << endl << "ICICI," << icici_new << endl << "WALLET," << wallet_new << endl << "BALANCE," << balance_new << endl << "EOF,999999";
		}
	}

	//Update the current_balances to app
	get();
	QString db = QString::fromUtf8(value[0].c_str());
	QString sbi = QString::fromUtf8(value[1].c_str());
	QString icici = QString::fromUtf8(value[2].c_str());
	QString wallet = QString::fromUtf8(value[3].c_str());
	lineEdit->setText( db );
	lineEdit_2->setText( sbi );
	lineEdit_3->setText( icici );
	lineEdit_4->setText( wallet );
	lineEdit_5->clear();
	lineEdit_6->clear();
}

void myBucks::about()
{
	QMessageBox::about(this, "About myBuck$",
        	                 "Version 2.04\n"
				 "Author: Sundaresan Venkatasubramanian\nEmail: sundaresan.24121988@gmail.com\nWebLink @ google+, Linkedin and facebook.\n"
                           	 "Bye.\n");
}

void myBucks::info()
{
	QMessageBox::about(this, "myBuck$ Information",
        	                 "Please update the csv files created now with your details for the first time. \n"
				 "Dont edit the files manually. \n"
                           	 "]-[@v3 a n!c3 d@y.\n");
}

void myBucks::gtotal()
{
	QString tot = QString::number((double)atof(value[0].c_str()) + (double)atof(value[1].c_str()) + (double)atof(value[2].c_str()) + (double)atof(value[3].c_str()) );
	QMessageBox::about(this, "myBuck$ Grand Total is...",
				tot);
}

void myBucks::get()
{
    std::ifstream  data("current_balances.csv");
    bool id_flag = true;
    std::string line;
    int i=0;
    while(std::getline(data,line))
    {
        std::stringstream  lineStream(line);
        std::string        cell;
        while(std::getline(lineStream,cell,','))
        {
            // You have a cell!!!!
            if (cell == "EOF")
		break;
            if(id_flag)
            { 
               id[i] = cell;
               id_flag = false;
            }
            else
            {
               value[i] = cell;
               id_flag = true;
               i++;  
            }
            std::cout << cell << std::endl;
        }
    }
}

QString myBucks::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%T", &tstruct);
    
    QString dime = QString::fromUtf8(buf);
    return dime;
}

void myBucks::handleSelectionChanged( int index ) {
	checkBox->setDisabled(index);
	checkBox_2->setDisabled(index);
}

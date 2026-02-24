#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox> // Required for displaying the output dialog

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

// Helper function to convert percentage to standard SA APS points
int calculateSubjectPoints(double percentage) {
    if (percentage >= 80.0) return 7;
    if (percentage >= 70.0) return 6;
    if (percentage >= 60.0) return 5;
    if (percentage >= 50.0) return 4;
    if (percentage >= 40.0) return 3;
    if (percentage >= 30.0) return 2;
    return 1;
}

void Dialog::on_pushButton_clicked()
{
    // 1. Retrieve the grades from the QDoubleSpinBox widgets in the UI
    double grades[7] = {
        ui->doubleSpinBox->value(),
        ui->doubleSpinBox_2->value(),
        ui->doubleSpinBox_3->value(),
        ui->doubleSpinBox_4->value(),
        ui->doubleSpinBox_5->value(),
        ui->doubleSpinBox_6->value(),
        ui->doubleSpinBox_7->value()
    };

    int totalAps = 0;
    double totalPercentage = 0.0;

    // 2. Loop through all 7 subjects to calculate points and sum the percentages
    for (int i = 0; i < 7; ++i) {
        totalAps += calculateSubjectPoints(grades[i]);
        totalPercentage += grades[i];
    }

    // Calculate average percentage across all 7 subjects
    double averagePercentage = totalPercentage / 7.0;

    // 3. Format the output message to include both the APS score and the average percentage mark
    QString resultMessage = QString("Total APS: %1 points\nAverage Grade: %2%")
                                .arg(totalAps)
                                .arg(averagePercentage, 0, 'f', 2);

    // 4. Display the results in a QMessageBox with the requested title
    QMessageBox::information(this, "Admission Point Score(APS)", resultMessage);
}

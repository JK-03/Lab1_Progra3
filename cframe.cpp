#include "cframe.h"
#include "ui_cframe.h"
#include <string>
#include <QMessageBox>
#include <QInputDialog>
#include <iostream>
#include <vector>

cframe::cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cframe)
{
    ui->setupUi(this);

    //Visual
    this->setWindowTitle("Laboratorio #1");

    //Abrir en Menú
    ui->tabWidget->setCurrentIndex(0);

}

cframe::~cframe()
{
    delete ui;
}

//EJERCICIO 1
void cframe::on_pushButton_clicked()
{
    std::string opcion = "";

    QMessageBox msgBox;
    msgBox.setText("Por favor, seleccione una opción:");

    QPushButton *opcion5 = msgBox.addButton("Salir", QMessageBox::ActionRole);
    QPushButton *opcion4 = msgBox.addButton("Ejercicio 4", QMessageBox::ActionRole);
    QPushButton *opcion3 = msgBox.addButton("Ejercicio 3", QMessageBox::ActionRole);
    QPushButton *opcion2 = msgBox.addButton("Ejercicio 2", QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == opcion2) {
        ui->tabWidget->setCurrentIndex(1);
    } else if (msgBox.clickedButton() == opcion3) {
        ui->tabWidget->setCurrentIndex(2);
    } else if (msgBox.clickedButton() == opcion4) {
        ui->tabWidget->setCurrentIndex(3);
    } else if (msgBox.clickedButton() == opcion5) {
        this->close();
    }
}

//EJERCICIO 2
double cframe::raizCuadrada(double numero) {
    double precision = 0.00001;
    double aproximacion = numero;
    double mejorAprox;

    do {
        mejorAprox = aproximacion;
        aproximacion = 0.5 * (mejorAprox + numero / mejorAprox);
    } while (abs(aproximacion - mejorAprox) > precision);

    return aproximacion;
}

void cframe::on_pushButton_2_clicked()
{
    bool ok;
    double numero = ui->spb_NumeroRaiz->text().toDouble(&ok);

    if (ok) {
        double raiz = raizCuadrada(numero);
        if (raiz == -1) {
            QMessageBox::warning(this, tr("Error"), tr("No debe de ingresar número negativos"));
        } else {
            double cuadrado = numero * numero;

            QString resultado = QString("La raíz cuadrada de %1 es: %2\nEl cuadrado de %1 es: %3").arg(numero).arg(raiz).arg(cuadrado);
            ui->TE_Resultado->setPlainText(resultado);
        }
    }
}

//EJERCICIO 3
double cframe::calcularImpuestoAnual(double salarioAnual) {
    double deduccionMedica = 40000.0;
    salarioAnual = std::max(0.0, salarioAnual - deduccionMedica);
    double impuestoAnual = 0.0;

    // Según la tabla
    if (salarioAnual <= 209369.62) {
        impuestoAnual = 0.0;
    } else if (salarioAnual <= 319251.54) {
        impuestoAnual = (salarioAnual - 209369.62) * 0.15;
    } else if (salarioAnual <= 742445.49) {
        impuestoAnual = (319251.54 - 209369.62) * 0.15 + (salarioAnual - 319251.54) * 0.20;
    } else {
        impuestoAnual = (319251.54 - 209369.62) * 0.15 + (742445.49 - 319251.54) * 0.20 + (salarioAnual - 742445.49) * 0.25;
    }

    return impuestoAnual;
}

double cframe::calcularImpuestoMensual(double salarioMensual) {
    double salarioAnual = salarioMensual * 12;
    double impuestoAnual = calcularImpuestoAnual(salarioAnual);
    return impuestoAnual / 12;
}

void cframe::on_pushButton_3_clicked() {
    double salario = ui->spb_Salario->value();

    QStringList opciones;
    opciones << "Mensual" << "Anual";
    bool ok;
    QString tipoSalario = QInputDialog::getItem(this, tr("Tipo de Salario"), tr("Seleccione el tipo de salario:"), opciones, 0, false, &ok);

    if (ok && !tipoSalario.isEmpty()) {
        double salarioAnual, salarioMensual, impuestoAnual, impuestoMensual;
        if (tipoSalario == "Mensual") {
            salarioMensual = salario;
            salarioAnual = salarioMensual * 12;
        } else {
            salarioAnual = salario;
            salarioMensual = salarioAnual / 12;
        }

        impuestoAnual = calcularImpuestoAnual(salarioAnual);
        impuestoMensual = calcularImpuestoMensual(salarioMensual);

        QString resultado = QString("Salario Anual: L%1\nImpuesto Anual: L%2\nImpuesto Mensual: L%3")
                                .arg(salarioAnual, 0, 'f', 2)
                                .arg(impuestoAnual, 0, 'f', 2)
                                .arg(impuestoMensual, 0, 'f', 2);

        ui->TE_ResultadoTabla->setPlainText(resultado);
    }
}

//EJERCICIO 4
std::vector<std::vector<int>> generarTrianguloPascal(int n) {
    std::vector<std::vector<int>> triangulo;

    //Calcular Valores
    for (int i = 0; i < n; ++i) {
        std::vector<int> fila(i + 1, 1);

        for (int j = 1; j < i; ++j) {
            fila[j] = triangulo[i - 1][j - 1] + triangulo[i - 1][j];
        }

        triangulo.push_back(fila);
    }
    return triangulo;
}

void cframe::on_pushButton_4_clicked()
{
    int n = ui->spb_Pascal->value();
    std::vector<std::vector<int>> triangulo = generarTrianguloPascal(n);

    QString resultado;
    for (const auto& fila : triangulo) {
        for (int num : fila) {
            resultado += QString::number(num) + " ";
        }
        resultado += "\n";
    }

    ui->TE_Pascal->setPlainText(resultado);
}

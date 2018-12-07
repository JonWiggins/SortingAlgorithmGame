#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QTimer>
#include <Box2DIncludes/Box2D/Collision/Shapes/b2Shape.h>
#include <Box2DIncludes/Box2D/Dynamics/b2Body.h>
#include <Box2D/Box2D.h>
#include <QDebug>
#include <QMouseEvent>
#include <iostream>
#include <algorithm>
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMouseTracking(true);

    // Size the texture
    texture.create(800, 500);

    //Copy Test.jpg from the project folder into the build folder
    QFile input_file(":/Images/Test.jpg");
    input_file.copy("Test.jpg");
    sprite_texture.loadFromFile("Test.jpg");

    //create array elements and give them to boxmaker
    createAndDisplayBoxes(randomVector(5, 90, 50));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::renderTexture);

    //16 millis means 60fps
    timer->start(16);
    sortType = 0;
    progressValue = 0;
    ui->stackedWidget->setCurrentIndex(0);
    font = ui->label_4->font();
    font.setPointSize(18);
    font.setBold(true);
}

bool MainWindow::checkVector(std::vector<int> originalOrder, int currentStep)
{
    sorts sorter;
    std::vector<int> currentSort = sorter.sorter(sortType, originalOrder, currentStep);
    std::vector<int> currentOrder = getBoxOrderVector();
    for(int index = 0; index < originalOrder.size(); index++)
    {
        if(currentSort.at(index) != currentOrder.at(index))
        {
            return false;
        }
    }
    return true;

}

//used to generate a vector of given length and with elements between 1 and maxsize + 1
std::vector<int> MainWindow::randomVector(int length, int maxSize, int minSize)
{
    std::vector<int> toReturn;
    std::srand(std::time(NULL));
    for(int counter = 0; counter < length; counter++)
    {
        toReturn.push_back(std::rand() % (maxSize - minSize + 1) + minSize);
    }
    return toReturn;
}

void MainWindow::createAndDisplayBoxes(std::vector<int> elements)
{
    int biggestBoxSize = 0;
    for(int element : elements)
    {
        if(element > biggestBoxSize)
        {
            biggestBoxSize = element;
        }
    }

    //draw each box, with the size of the biggest box + 60
    int paddingsize = biggestBoxSize + 5;

    int currentPos = 100;

    std::vector<int*> boxInfo;


    for(int element : elements)
    {
        int* toAdd = new int[3]{element, currentPos, 250};
        currentPos += paddingsize + element;
        boxInfo.push_back(toAdd);

    }

    this->world = new box2dhandler(boxInfo, 800, 500);

}

void MainWindow::renderTexture() {
    // Clear the whole texture with red color
    texture.clear(sf::Color::White);
    auto position = world->getBoxPositions();

    this->world->updateWorld();

    std::vector<std::tuple<int,int, float32, int>> boxLocations = world->getBoxPositions();
    for(int counter = 0; counter < boxLocations.size(); counter++)
    {
        std::tuple<int, int, float32, int> location = boxLocations.at(counter);
        sf::RectangleShape square(sf::Vector2f(std::get<3>(location), std::get<3>(location)));
        square.setFillColor(sf::Color::Black);
        square.setPosition(std::get<0>(location), 500 - (std::get<1>(location) + std::get<3>(location)));
        square.rotate(std::get<2>(location));

        texture.draw(square);   // shape is a sf::Shape

        square.setPosition(x,y);
    }

    texture.display();

    // Set to a QImage
    QImage qi(texture.getTexture().copyToImage().getPixelsPtr(), 800,500, QImage::Format_ARGB32);
    qi = qi.rgbSwapped();

       ui->label->setPixmap(QPixmap::fromImage(qi));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    float tempX = event ->x() - ui->label->x();
    float tempY = event ->y() - ui->label->y();

    world->userMove(0, tempX, 500 - tempY);

}

std::vector<int> MainWindow::getBoxOrderVector(){
    std::vector<int> toReturn;

    std::vector<std::tuple<int,int, float32, int>> boxLocations = world->getBoxPositions();

    std::vector<int> xPositions;
    for(auto box : boxLocations)
        xPositions.push_back(std::get<0>(box));

    //this sort happens inscope so it does not effect anything else
    std::sort(xPositions.begin(), xPositions.end());

    for(int xPos : xPositions){
        //find the associated box and add it to the toReturn vector
        for(auto box : boxLocations){
            if(std::get<0>(box) == xPos)
                toReturn.push_back(std::get<3>(box));
        }
    }

    return toReturn;
}



void MainWindow::on_mergeButton_clicked()
{
    ui->sortInfoLabel->setText("Merge sort is an algorithm which takes th e"
                               "approach of dividing the task to be done into "
                               "smaller chunks. First it splits the given array "
                               "in half, then uses merge sort on each half until "
                               "the size of each individual array is 1. Then it "
                               "goes back up merging each half of the array until "
                               "it is fully merged. A merge is putting the two "
                               "arrays together and outputting a sorted array. This "
                               "uses less comparisons than some other sorting "
                               "algorithms because each half of the arrays to be "
                               "merged are already sorted."
                               "\nExample:"
                               "\nDividing the array:"
                               "\n[5 1 4 2 8 3 7]"
                               "\n[5 1 4 2] | [8 3 7]"
                               "\n[5 1] | [4 2] | [8 3] | [7]"
                               "\n[5] | [1] | [4] | [2] | [8] | [3] | [7]"
                               "\nMerging the first pair of arrays:"
                               "\n[1 5] | [4] | [2] | [8] | [3] | [7]"
                               "\nMerging the next pair:"
                               "\n[1 5] | [2 4] | [8] | [3] | [7]"
                               "\nMerging the last pair:"
                               "\n[1 5] | [2 4] | [3 8] | [7]"
                               "\nMerging the first pair arrays again:"
                               "\n[1 2 4 5] | [3 8] | [7]"
                               "\nMerging the next two:"
                               "\n[1 2 4 5] | [3 7 8]"
                               "\nCompleting the merge sort:"
                               "\n[1 2 3 4 5 7 8]");
    sortType = 4; //Merge sort is 4
    sorts sorter;

    //create array elements and give them to boxmaker
    originState = randomVector(5,90,50);
    currentIteration = 1;
    createAndDisplayBoxes(sorter.sorter(sortType, originState, currentIteration));

    ui->stackedWidget->setCurrentIndex(1);
    ui->label_4->setText(" Merge Sort");
    ui->label_4->setFont(font);
}

void MainWindow::on_insertButton_clicked()
{
    ui->sortInfoLabel->setText("Insertion sort works by iterating over the entirety"
                               " of the array while ‘inserting’ each element into the"
                               " previously sorted elements. Upon beginning on an array"
                               ", the first element of the array is left where it is,"
                               " as in the subset of one element, it is sorted. Next, "
                               "the second element is compared to the previously sorted "
                               "element and inserted either before or after it. This process "
                               "of inserting each element into the previously sorted "
                               "elements continues until the entire array is sorted. This"
                               " insertion process gives Insertion Sort a high swap count,"
                               " as in the worst case, an element that needs to be inserted "
                               "at the beginning of the array will require each previously "
                               "sorted element to be swapped back one position."
                               "\nFirst Iteration:"
                               "\n[5 1 4 2 8] -> [5 1 4 2 8]"
                               "\nSecond Iteration:"
                               "\n[5 1 4 2 8] -> [1 5 4 2 8]"
                               "\nThird Iteration:"
                               "\n[5 1 4 2 8] -> [1 4 5 2 8]"
                               "\nFourth Iteration:"
                               "\n[1 4 5 2 8] -> [1 2 4 5 8]"
                               "\nFifth Iteration:"
                               "\n[1 2 4 5 8] -> [1 2 4 5 8]");
    sortType = 2; //Insertion sort is 2
    sorts sorter;

    //create array elements and give them to boxmaker
    originState = randomVector(5,90,50);
    currentIteration = 1;
    createAndDisplayBoxes(sorter.sorter(sortType, originState, currentIteration));

    ui->stackedWidget->setCurrentIndex(1);
    ui->label_4->setText("Insertion Sort");
    ui->label_4->setFont(font);
}


void MainWindow::on_bubbleButton_clicked()
{
    ui->sortInfoLabel->setText("Bubble Sort is one of the simplest algorithms"
                               " but it comes with doing one of the most "
                               "comparisons for a sort. It works by iterating "
                               "through each element of the array and swapping "
                               "the element to the right of it if it is bigger than "
                               "the current element. When a full iteration is "
                               "completed the largest element has been moved to the"
                               " end and it needs to do another pass, but because the"
                               " largest element is at the end it does not need to "
                               "get sorted again so it gets discluded from the next "
                               "pass. This loop repeats for every element in the array"
                               " until they are all sorted."
                               "\nExample:"
                               "\nFirst Loop:"
                               "\n[5 1 4 2 8] -> [1 5 4 2 8]"
                               "\n[1 5 4 2 8] -> [1 4 5 2 8]"
                               "\n[1 4 5 2 8] -> [1 4 2 5 8]"
                               "\n[1 4 2 5 8] -> [1 4 2 5 8]"
                               "\nSecond Loop:"
                               "\n[1 4 2 5 8] -> [1 4 2 5 8]"
                               "\n[1 4 2 5 8] -> [1 2 4 5 8]"
                               "\n[1 2 4 5 8] -> [1 2 4 5 8]"
                               "\nThird Loop:"
                               "\n[1 2 4 5 8] -> [1 2 4 5 8]"
                               "\n[1 2 4 5 8] -> [1 2 4 5 8]"
                               "\n[1 2 4 5 8] -> [1 2 4 5 8]");
    sortType = 3; //bubble sort is 3
    sorts sorter;

    //create array elements and give them to boxmaker
    originState = randomVector(5,90,50);
    currentIteration = 1;
    createAndDisplayBoxes(sorter.sorter(sortType, originState, currentIteration));

    ui->stackedWidget->setCurrentIndex(1);
    ui->label_4->setText("Bubble Sort");
    ui->label_4->setFont(font);
}


void MainWindow::on_selectButton_clicked()
{
    ui->sortInfoLabel->setText("From a programming perspective, Selection Sort "
                               "is one of the simplest sorting algorithms to implement."
                               " However, this simplicity to program comes at a cost of "
                               "runtime or comparison count. Selection sort works by sectioning "
                               "the array into two parts, a sorted, and unsorted part. At the "
                               "beginning of sorting, the algorithm iterates through the entirety"
                               " of the array to find the smallest element. This element "
                               "is then swapped from its current position to the 0th index. "
                               "This process it then repeated, finding the smallest element "
                               "in the remaining section of the array, and swapping it into "
                               "the next index. This process is repeated until every element "
                               "has been sorted. It should be noted that even if the array is "
                               "sorted before every element has been reached, the remaining "
                               "elements will still be selected and sorted."
                               "\nExample:"
                               "\nFirst Iteration:"
                               "\n[5 1 4 2 8] -> [1 5 4 2 8]"
                               "\nSecond Iteration:"
                               "\n[1 5 4 2 8] -> [1 2 4 5 8]"
                               "\nThird Iteration:"
                               "\n[1 2 4 5 8] -> [1 2 4 5 8]"
                               "\nFourth Iteration:"
                               "\n[1 2 4 5 8] -> [1 2 4 5 8]"
                               "\nFifth Iteration:"
                               "\n[1 2 4 5 8] -> [1 2 4 5 8]");
    sortType = 1; //section sort is 1
    sorts sorter;

    //create array elements and give them to boxmaker
    originState = randomVector(5,90,50);
    currentIteration = 1;
    createAndDisplayBoxes(sorter.sorter(sortType, originState, currentIteration));

    ui->stackedWidget->setCurrentIndex(1);
    ui->label_4->setText("Selection Sort");
    ui->label_4->setFont(font);

}

void MainWindow::on_NextButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_CheckButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
     switch(sortType)
     {
     case 1:
         ui->selectButton->setStyleSheet("background-color: rgb(0, 255, 0);");
         break;
     case 2:
         ui->insertButton->setStyleSheet("background-color: rgb(0, 255, 0);");
         break;
     case 3:
         ui->bubbleButton->setStyleSheet("background-color: rgb(0, 255, 0);");
         break;
     case 4:
         ui->mergeButton->setStyleSheet("background-color: rgb(0, 255, 0);");
         break;
    }
     if(!sortsCompleted[sortType])
     {
         progressValue += 25;
     }
     sortsCompleted[sortType] = true;
     ui->progressBar->setValue(progressValue);

}

void MainWindow::on_Home_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionGame_Information_triggered()
{
    QMessageBox::information(this,"Tutorial","Select a sort to learn, Test your knowledge of this sort "
                                             "The following boxes a X sort partway through sortin, "
                                             "click and drag to move them into how they will be positioned "
                                             "in the array after the next sort iteration");
}

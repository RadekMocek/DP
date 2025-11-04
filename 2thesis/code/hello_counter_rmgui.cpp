// Předpokládejme třídu App se členy counter, layout,
// button_counter_decrement, label_counter_value atd.

void App::init() {
    button_counter_decrement = new QPushButton("-");
    layout->addWidget(button_counter_decrement);
    connect(button_counter_decrement, &QPushButton::clicked, this, &App::on_button_decrement_clicked);

    label_counter_value = new QLabel("");
    layout->addWidget(label_counter_value);

    button_counter_increment = new QPushButton("+");
    layout->addWidget(button_counter_increment);
    connect(button_counter_increment, &QPushButton::clicked, this, &App::on_button_increment_clicked);

    label_hello = new QLabel("Hello!");
    layout->addWidget(label_hello);

    counter = 1;
    on_counter_update();
}

void App::on_button_decrement_clicked() {
    counter--;
    on_counter_update();
}

void App::on_button_increment_clicked() {
    counter++;
    on_counter_update();
}

void App::on_counter_update() {
    label_counter_value->setText(QString::number(counter));

    button_counter_decrement->setEnabled(counter != 1);
    button_counter_increment->setEnabled(counter != 5);

    label_hello->setVisible(counter == 3);
}
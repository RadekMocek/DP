using System;
using Avalonia.Controls;
using Avalonia.Interactivity;

namespace AvaloniaApplication1;

public partial class MainWindow : Window
{
    private int _counter;

    public MainWindow()
    {
        InitializeComponent();

        _counter = 1;
        CounterUpdated();
    }

    private void ButtonIncrClicked(object? sender, RoutedEventArgs e)
    {
        _counter++;
        CounterUpdated();
    }

    private void ButtonDecrClicked(object? sender, RoutedEventArgs e)
    {
        _counter--;
        CounterUpdated();
    }

    private void CounterUpdated()
    {
        LabelCounter.Content = $"{_counter}";

        ButtonDecr.IsEnabled = _counter != 1;
        ButtonIncr.IsEnabled = _counter != 5;

        LabelHello.IsVisible = _counter == 3;
    }

    private void MenuExitClicked(object? sender, RoutedEventArgs e)
    {
        Environment.Exit(0);
    }
}
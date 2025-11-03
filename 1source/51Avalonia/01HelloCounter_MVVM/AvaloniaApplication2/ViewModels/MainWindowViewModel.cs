using System;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace AvaloniaApplication2.ViewModels;

public partial class MainWindowViewModel : ViewModelBase
{
    [ObservableProperty] private int _counter = 1;

    [ObservableProperty] private bool _isButtonDecrEnabled = false;
    [ObservableProperty] private bool _isButtonIncrEnabled = true;
    [ObservableProperty] private bool _isLabelHelloVisible = false;

    [RelayCommand]
    private void MenuExitClicked()
    {
        Environment.Exit(0);
    }

    [RelayCommand]
    private void ButtonDecrClicked()
    {
        Counter--;
        CounterUpdated();
    }

    [RelayCommand]
    private void ButtonIncrClicked()
    {
        Counter++;
        CounterUpdated();
    }

    private void CounterUpdated()
    {
        IsButtonDecrEnabled = Counter != 1;
        IsButtonIncrEnabled = Counter != 5;

        IsLabelHelloVisible = Counter == 3;
    }
}
import csv
import pathlib
from enum import StrEnum
from os import listdir
from os.path import isfile, join
from typing import Tuple

import matplotlib
import matplotlib.pyplot as plt

matplotlib.use("TkAgg")

PATH = pathlib.Path(__file__).parent


class Metric(StrEnum):
    RAM = "RAM Resident/Working Set Size [MiB]"
    CPU = "System CPU [%]"
    DUR = "DUR [ms]"


class Lib(StrEnum):
    DEAR = "DearImGui"
    EGUI = "egui"
    QT = "Qt"


def lib_color(lib: Lib):
    match lib:
        case Lib.DEAR:
            return "blue"
        case Lib.EGUI:
            return "orange"
        case Lib.QT:
            return "green"


class BenchRun:
    def __init__(self, name):
        self.name = name
        self.timestamp = []
        self.fps = []
        self.n_nodes = []
        self.mem_mib = []
        self.cpu_usage = []

        self.time_diff = []

    def append_csv_row(self, row: list[str]):
        current_timestamp = int(row[0])
        self.timestamp.append(current_timestamp)
        self.fps.append(int(float(row[1])))
        self.n_nodes.append(int(row[2]))
        self.mem_mib.append(float(row[3]))
        self.cpu_usage.append(float(row[4]))

        if len(self.timestamp) == 1:
            self.time_diff.append(current_timestamp)
        else:
            self.time_diff.append(current_timestamp - self.timestamp[-2])

    def get_duration_str(self):
        duration = self.timestamp[-1] - self.timestamp[0]
        return f"{duration / 1000} seconds"

    def get_metric(self, which: Metric):
        match which:
            case Metric.CPU:
                return self.cpu_usage
            case Metric.RAM:
                return self.mem_mib
            case Metric.DUR:
                return self.time_diff


METRICS = [Metric.RAM, Metric.CPU, Metric.DUR]
LIBS = [Lib.DEAR, Lib.EGUI, Lib.QT]
BENCHES = [("b0", "LIGHT"), ("b1", "HEAVY"), ("b2", "GRADUAL")]
MODS = [("shon", "Syntax Highlight ON"), ("shoff", "Syntax Highlight OFF"), ("txoff", "Text editor OFF")]


def all_(runs, devices, info):
    for bench_pair in BENCHES:
        fig, axs = plt.subplots(len(devices), len(METRICS))
        plt.suptitle(f"Benchmark {bench_pair[1]} {info}")
        for (row, device_pair) in enumerate(devices):
            for (col, metric) in enumerate(METRICS):
                cell_axs = axs[row, col]
                cell_axs.set_title(metric)
                for lib in LIBS:
                    key = f"{str(lib)}_{device_pair[0]}_{bench_pair[0]}_"

                    cell_axs.plot(runs[key + "shon"].get_metric(metric)[2:],
                                  color=lib_color(lib), linestyle="solid", label=f"{str(lib)} SHON")

                    cell_axs.plot(runs[key + "shoff"].get_metric(metric)[2:],
                                  color=lib_color(lib), linestyle="dashed", label=f"{str(lib)} SHOFF")

                    cell_axs.plot(runs[key + "txoff"].get_metric(metric)[2:],
                                  color=lib_color(lib), linestyle="dotted", label=f"{str(lib)} TXOFF")
                    if col == 2:
                        cell_axs.legend(loc="center left", bbox_to_anchor=(1, 0.5))

        # fig.tight_layout()
    plt.show()


def alt_(runs, devices, bench_id, versus_mod: Tuple[str, str]):
    for metric in METRICS:
        fig, axs = plt.subplots(len(devices), 3)
        plt.suptitle(f"{bench_id} :: {str(metric)}")
        for (row, device) in enumerate(devices):
            for lib in LIBS:
                key0 = f"{lib}_{device[0]}_{bench_id}_{versus_mod[0]}"
                key1 = f"{lib}_{device[0]}_{bench_id}_{versus_mod[1]}"
                for i in [0, 1]:
                    axs[row, i].plot(runs[key0].get_metric(metric)[2:], color=lib_color(lib))
                for i in [0, 2]:
                    axs[row, i].plot(runs[key1].get_metric(metric)[2:], color=lib_color(lib), linestyle="dashed")

        # Add row and col headers
        for ax, col in zip(axs[0], ["both", versus_mod[0], versus_mod[1]]):
            ax.set_title(col)

        for ax, row in zip(axs[:, 0], devices):
            ax.set_ylabel(row[1], size="large")

    plt.show()


def main():
    path = PATH / "csv_nodes"
    filenames = [f for f in listdir(path) if isfile(join(path, f))]
    runs: dict[str, BenchRun] = {}
    for filename in filenames:
        with open(path / filename, "r") as f:
            reader = csv.reader(f)
            run = BenchRun(filename)
            is_first = True
            for row in reader:
                if is_first:
                    is_first = False
                    continue
                run.append_csv_row(row)
            runs[filename[8:-15]] = run

    for key, run in runs.items():
        print(f"{key.ljust(26)}{run.get_duration_str()}")

    devices_all = [
        ("win", "Win10 Desktop"),  # 0
        ("lin", "Mint laptop, integrated GPU"),  # 1
        ("ling", "Mint laptop, dedicated GPU"),  # 2
        ("OLD", "Mint laptop OLD")  # 3
    ]

    dev_linux_both = [devices_all[1], devices_all[2]]
    dev_lini_win = [devices_all[1], devices_all[0]]
    dev_lin_new_old = [devices_all[2], devices_all[3]]

    # all_(runs, dev_linux_both, "on Mint laptop\nROW1: integrated GPU\nROW2: dedicated GPU")
    # all_(runs, dev_lini_win, "\nROW1: Mint laptop integrated GPU\nROW2: Win10 desktop dedicated GPU")
    # all_(runs, dev_lin_new_old, " !!\nROW1: 2016 mint laptop igpu\nROW2: 2011 mint laptop igpu")

    # alt_(runs, dev_lini_win, BENCHES[0][0], ("shon", "shoff"))
    alt_(runs, dev_lin_new_old, "b2", ("shon", "txoff"))


if __name__ == "__main__":
    main()

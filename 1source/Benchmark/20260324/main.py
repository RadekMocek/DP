import pathlib
from os import listdir
from os.path import isfile, join

import matplotlib
import matplotlib.pyplot as plt

import csv

matplotlib.use("TkAgg")

PATH = pathlib.Path(__file__).parent


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


def main():
    path = PATH / "csv"
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
            runs[filename[11:-4]] = run

    for key, run in runs.items():
        print(f"{key}\t\t{run.get_duration_str()}")

    device_names = ["win10 desktop", "mint laptop"]
    bench_names = ["LIGHT", "HEAVY", "GRADUAL"]

    for d_i, d in enumerate(["win", "lin"]):
        for b_i in range(0, 3):
            run_dear_shon = runs[f"DearImGui_{b_i}_{d}_on"]
            run_dear_shoff = runs[f"DearImGui_{b_i}_{d}_off"]
            run_qt_shon = runs[f"Qt_{b_i}_{d}_on"]
            run_qt_shoff = runs[f"Qt_{b_i}_{d}_off"]

            x = run_dear_shon.timestamp
            plt.figure()
            plt.suptitle(f"{bench_names[b_i]} ({device_names[d_i]})")
            plt.subplot(1, 3, 1)
            plt.title("RAM MiB")
            plt.plot(x, run_dear_shon.mem_mib, color="palevioletred", linestyle="-", label="DearImGui SH ON")
            plt.plot(x, run_dear_shoff.mem_mib, color="palevioletred", linestyle="--", label="DearImGui SH OFF")
            plt.plot(x, run_qt_shon.mem_mib, color="green", linestyle="-", label="Qt SH ON")
            plt.plot(x, run_qt_shoff.mem_mib, color="green", linestyle="--", label="Qt SH OFF")
            plt.subplot(1, 3, 2)
            plt.title("CPU %")
            plt.plot(x, run_dear_shon.cpu_usage, color="palevioletred", linestyle="-", label="DearImGui SH ON")
            plt.plot(x, run_dear_shoff.cpu_usage, color="palevioletred", linestyle="--", label="DearImGui SH OFF")
            plt.plot(x, run_qt_shon.cpu_usage, color="green", linestyle="-", label="Qt SH ON")
            plt.plot(x, run_qt_shoff.cpu_usage, color="green", linestyle="--", label="Qt SH OFF")
            plt.subplot(1, 3, 3)
            plt.title("Duration ms")
            plt.plot(x, run_dear_shon.time_diff, color="palevioletred", linestyle="-", label="DearImGui SH ON")
            plt.plot(x, run_dear_shoff.time_diff, color="palevioletred", linestyle="--", label="DearImGui SH OFF")
            plt.plot(x, run_qt_shon.time_diff, color="green", linestyle="-", label="Qt SH ON")
            plt.plot(x, run_qt_shoff.time_diff, color="green", linestyle="--", label="Qt SH OFF")
            plt.legend()
            plt.savefig(f"figs/{d}_{b_i}.png")
    # plt.show()


if __name__ == "__main__":
    main()

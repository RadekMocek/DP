import csv
import pathlib
from os import listdir
from os.path import isfile, join
import matplotlib.pyplot as plt

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
        print(f"{key}\t\t{run.get_duration_str()}")

    benches = [("b0","LIGHT"), ("b1","HEAVY"), ("b2","GRADUAL")]
    devices = [("win", "Win10 Desktop"), ("lin", "Mint laptop, integrated GPU"), ("ling", "Mint laptop, dedicated CPU")]

    for bench_pair in benches:
        for device_pair in devices:
            pass


if __name__ == "__main__":
    main()

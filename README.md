# Brain

`brain` is a C++ based Robot Simulation, with an integral integration with Python.

## Usage
```sh
./brain <config-file-path>
```

Where `config-file` is the path of a `yaml` config file, controlling both brain attributes (e.g. num of motors) and execution params (e.g. how long to run).
You may find config file examples under the resources directory.

Note: `brain` does not have to be executed from its directory

## How to Build

In the project root dir call: 

```sh
./build.sh <target-dir>
```

Where `target-dir` is a non-existing directory.

For example:

```sh
./build.sh release
```

The `brain` executalble, along with relevant libraries, would be created in the specified target-dir.
You may then execute brain. E.g.:

```sh
./release/brain resources/config-example-01.yml
```

**Note:** In order to build `brain` you would need [pybind11](https://pybind11.readthedocs.io/en/stable/) to be installed on your server. If needed please follwo the [installation instruction](https://pybind11.readthedocs.io/en/stable/installing.html).


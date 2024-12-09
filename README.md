# todo

Command line tool written in `C` for personal uses.

## Installation

```bash
git clone https://github.com/CesareDev/todo.git
cd todo
./generate.sh
cd build/release/todo
make
```

## Usage

The executable is located to the `build/release/todo/` or `build/debug/todo/` directory. The you have to add this line to your session starting file (e.g. `.bashrc`):

```bash
todo -l
```

This works if you have the `todo` executable in your `PATH`. If you don't want to add the executable to your `PATH` you can use the full path to the executable. Obviously you must not edit the generated `.todo` file manually.

## Limitations

For now the tool can't delete single reminders. You have to call `todo -c` to clean all the reminders file.

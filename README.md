# ƒMusic

[![Screenshot](https://i.imgur.com/rRUIXpT.png)](https://www.youtube.com/watch?v=lIOiAK0x4vA)

A functional music generator, that is, a program designed to generate real-time MIDI output through functions written by musicians or programmers. There is both a GUI and a command line version available.

## Songs

The songs are written in [Lua](https://www.lua.org) and each one consists of a single function `f` that takes a single argument `t` which is the number of milliseconds since the song started. The function `f` then returns three integers representing a [MIDI message](https://en.wikipedia.org/wiki/MIDI#Messages) (i.e. a status byte and two data bytes). For example, a "song" that consists of random notes played at random times is as follows:

```lua
math.randomseed(os.time())

function f(t)
	if (t % math.random(400, 1000)) == 0 then
		return 144, math.random(45, 69), math.random(60, 120)
	end
	return 0, 0, 0
end
```

For some more interesting songs have a look at the `.fmu` files in the [examples](examples/) folder.

## Examples

Both of these examples are using the [CLI](cli/) program and [Reaktor 5](http://www.native-instruments.com/en/products/komplete/synths/reaktor-5/) to turn the MIDI messages into music! The [fugue](https://en.wikipedia.org/wiki/Fugue) by Bach (the first link) seems to work better. Perhaps this is due to the mathematical structure of a fugue but that is merely a guess.

* [Markov chain generated music from Bach's "Toccata and Fugue in D minor"](https://www.youtube.com/watch?v=lIOiAK0x4vA)
* [Markov chain generated music from Satie's "Gymnopédies" and "Trois Gnossiennes"](https://www.youtube.com/watch?v=H3xgdDTvvlc)

## Dependencies

Many thanks to the developers of the following (awesome) libraries!

* [Qt](https://www.qt.io/)
* [LuaJIT](http://luajit.org/)
* [RtMidi](https://github.com/thestk/rtmidi)

## Known Issues

1. No binaries have been uploaded so to use the program you will have to compile it yourself using [CMake](https://cmake.org/)
2. No testing of the program has taken place on Linux or Windows (only recent versions of OS X) so it is not know if it can compile and run properly on these systems.
3. The program has not been updated for a while so it's still using older versions of the libraries listed above

## License

The ƒMusic program and related files are released under the [MIT license](LICENSE). The [MIDI files](examples/midi/) used by the [Markov Generator Song](examples/markov.fmu) are, as far as I know, in the public domain, but I am happy to remove them if this proves not to be the case.

#! /usr/bin/env ruby
require 'midilib/sequence'
require 'optparse'

options = {}
OptionParser.new do |opts|
    opts.banner = "Usage: #{__FILE__} midi_file [options]"

    #Default values
    options[:channel]    = 1
    options[:limit]      = 300
    options[:timestamps] = false

    opts.on('-t', '--timestamps', "Created the array using timestamps rather than duration") do |timestamps|
        options[:timestamps] = true;
    end

    opts.on('-l', '--limit THRESHOLD', "Limits the amount of notes") do |limit|
        options[:limit] = limit.to_i;
    end

    opts.on('-o', '--arduinofile FILE', "Output arduino file") do |arduinofile|
        options[:arduinofile] = arduinofile;
    end

    opts.on('-c', '--channel AMOUNT_OF_CHANNEL', "Channel to be appear on in the tone arrays (Max 2)") do |x|
        if x.to_i > 2
            puts opts
            exit
        end
        options[:channel] = x.to_i
    end

    if !File.exists?(ARGV[0])
        puts opts
        exit
    end
    options[:file] = File.open(ARGV[0], 'rb')

    opts.on( '-h', '--help', 'Display this screen' ) do
        puts opts
        exit
    end
end.parse!



#Initialization and information display
seq = MIDI::Sequence.new()

puts "Available tracks:"
seq.read(options[:file]) do |track, num_tracks, i|
    if track
        puts "#{i - 1}: #{track.name} #{track.instrument ? track.instrument : ''}"
    end
end

pulse = seq.pulses_to_seconds(1)*1000
puts "\nBPM: #{seq.beats_per_minute} - Pulse: #{pulse} ms\n"

puts "Which track do you want to convert to Arduino tone?"
tracks = Array.new
(1..options[:channel]).each do |x|
    print "#{x}?: "
    tracks << STDIN.gets.to_i
end



#Information gathering
arr_note_data   = Array.new

(0..(options[:channel]-1)).each do |x|
    arr_note_data << Array.new
    note_on   = false
    h         = Hash.new
    timestamp = 0

    seq.each_with_index do |track, i|
        if i == tracks[x]
            track.each do |e|

                delta_time = (e.delta_time*pulse).to_i      #Time since last event in ms
                timestamp += delta_time

                if e.class.name == 'MIDI::NoteOn' || e.class.name == 'MIDI::NoteOff'
                    if (not note_on) && (e.class.name == 'MIDI::NoteOn')
                        h['timestamp'] = timestamp
                        h['note']      = e.pch_oct
                        note_on        = true
                    elsif note_on && (e.class.name == 'MIDI::NoteOff')
                        if e.pch_oct == h['note']
                            h['duration'] = timestamp - h['timestamp']
                            note_on       = false
                            arr_note_data[x] << h.clone
                        end
                    end
                end
            end
        end
    end

    if arr_note_data[x].length == 0
        puts "track #{tracks[x]} does not contain any note"
        exit
    end
end



#Building the two arrays
arr_note     = Array.new
arr_duration = Array.new

(0..(options[:channel]-1)).each do |x|
    arr_note     << Array.new
    arr_duration << Array.new

    arr_note_data[x].each_with_index do |note_data, index|
        if index == 0 && note_data['timestamp'] != 0
            arr_note[x]     << 0
            if options[:timestamps]
                arr_duration[x] << 0
            else
                arr_duration[x] << note_data['timestamp']
            end
        end

        if options[:limit] < arr_note[x].length
            break
        end

        arr_note[x]     << note_data['note']

        if options[:timestamps]
            arr_duration[x] << note_data['timestamp']
        else
            arr_duration[x] << note_data['duration']
        end

        if note_data != arr_note_data[x].last && note_data['timestamp'] + note_data['duration'] != arr_note_data[x][index + 1]['timestamp']
            timestamp_shift = options[:timestamps] ? arr_duration[x].last : 0
            arr_note[x] << 0
            arr_duration[x] << timestamp_shift + (arr_note_data[x][index + 1]['timestamp'] - note_data['timestamp'] - note_data['duration'])
        end
    end
end



sketch = ""

if options.key?:arduinofile
    sketch = "#include <TonePlayer.h>\n\n/*************************************************\n * Public Constants\n *************************************************/\n#define NOTE_0   0\n#define NOTE_B0  31\n#define NOTE_C1  33\n#define NOTE_CS1 35\n#define NOTE_D1  37\n#define NOTE_DS1 39\n#define NOTE_E1  41\n#define NOTE_F1  44\n#define NOTE_FS1 46\n#define NOTE_G1  49\n#define NOTE_GS1 52\n#define NOTE_A1  55\n#define NOTE_AS1 58\n#define NOTE_B1  62\n#define NOTE_C2  65\n#define NOTE_CS2 69\n#define NOTE_D2  73\n#define NOTE_DS2 78\n#define NOTE_E2  82\n#define NOTE_F2  87\n#define NOTE_FS2 93\n#define NOTE_G2  98\n#define NOTE_GS2 104\n#define NOTE_A2  110\n#define NOTE_AS2 117\n#define NOTE_B2  123\n#define NOTE_C3  131\n#define NOTE_CS3 139\n#define NOTE_D3  147\n#define NOTE_DS3 156\n#define NOTE_E3  165\n#define NOTE_F3  175\n#define NOTE_FS3 185\n#define NOTE_G3  196\n#define NOTE_GS3 208\n#define NOTE_A3  220\n#define NOTE_AS3 233\n#define NOTE_B3  247\n#define NOTE_C4  262\n#define NOTE_CS4 277\n#define NOTE_D4  294\n#define NOTE_DS4 311\n#define NOTE_E4  330\n#define NOTE_F4  349\n#define NOTE_FS4 370\n#define NOTE_G4  392\n#define NOTE_GS4 415\n#define NOTE_A4  440\n#define NOTE_AS4 466\n#define NOTE_B4  494\n#define NOTE_C5  523\n#define NOTE_CS5 554\n#define NOTE_D5  587\n#define NOTE_DS5 622\n#define NOTE_E5  659\n#define NOTE_F5  698\n#define NOTE_FS5 740\n#define NOTE_G5  784\n#define NOTE_GS5 831\n#define NOTE_A5  880\n#define NOTE_AS5 932\n#define NOTE_B5  988\n#define NOTE_C6  1047\n#define NOTE_CS6 1109\n#define NOTE_D6  1175\n#define NOTE_DS6 1245\n#define NOTE_E6  1319\n#define NOTE_F6  1397\n#define NOTE_FS6 1480\n#define NOTE_G6  1568\n#define NOTE_GS6 1661\n#define NOTE_A6  1760\n#define NOTE_AS6 1865\n#define NOTE_B6  1976\n#define NOTE_C7  2093\n#define NOTE_CS7 2217\n#define NOTE_D7  2349\n#define NOTE_DS7 2489\n#define NOTE_E7  2637\n#define NOTE_F7  2794\n#define NOTE_FS7 2960\n#define NOTE_G7  3136\n#define NOTE_GS7 3322\n#define NOTE_A7  3520\n#define NOTE_AS7 3729\n#define NOTE_B7  3951\n#define NOTE_C8  4186\n#define NOTE_CS8 4435\n#define NOTE_D8  4699\n#define NOTE_DS8 4978\n\n"

    (0..(options[:channel]-1)).each do |x|
        sketch << "prog_uint16_t melody_#{x+1}[] PROGMEM        = {"
        arr_note[x].each do |note|
            sketch << "NOTE_#{note},".gsub('#', 'S')
        end

        sketch << "};\nprog_uint16_t noteDurations_#{x+1}[] PROGMEM = {"
        arr_duration[x].each do |duration|
            sketch << "#{duration},"
        end
        sketch << "};\n"
        sketch << "int number_of_note_#{x+1} = #{arr_note[x].length};\n\n"
    end

    (0..(options[:channel]-1)).each do |x|
        sketch << "const int pin_1     = 9;\n"  if x == 0
        sketch << "const int pin_2     = 11;\n" if x == 1
    end

    sketch << "\n"

    (0..(options[:channel]-1)).each do |x|
        sketch << "TonePlayer toneplayer_#{x+1}(pin_#{x+1}, melody_#{x+1}, noteDurations_#{x+1}, number_of_note_#{x+1}, #{x+1}, #{options[:timestamps]});\n"
    end

    sketch << "\n\nvoid setup(){}\n\nvoid loop(){\n"

    sketch << "    while(!toneplayer_1.finished()#{options[:channel] == 2 ? " || !toneplayer_2.finished()" : ""}){\n        toneplayer_1.playNote();\n#{options[:channel] == 2 ? "        toneplayer_2.playNote();\n" : ""}    }\n\n    toneplayer_1.resetPointer();\n#{options[:channel] == 2 ? "    toneplayer_2.resetPointer();" : ""}"

    sketch << "\n\n}"
    out = File.open options[:arduinofile], "w"
    out.write sketch
    out.close
else
    (0..(options[:channel]-1)).each do |x|
        sketch << "int melody_#{x+1}[] = {"
        arr_note[x].each do |note|
            sketch << "NOTE_#{note},".gsub('#', 'S')
        end

        sketch << "};\n\nint noteDurations_#{x+1}[] = {"
        arr_duration[x].each do |duration|
            sketch << "#{duration},"
        end

        sketch << "};\n"
        sketch << "int number_of_note_#{x+1} = #{arr_note.length};\n\n"
    end
end

puts sketch;

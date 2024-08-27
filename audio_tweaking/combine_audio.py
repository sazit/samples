from pydub import AudioSegment

def edit_mp3(file_path, start_sec, end_sec):
    """
    Edits the MP3 file by trimming it from start_sec to end_sec.
    Args:
        file_path (str): The path to the MP3 file.
        start_sec (int): The start time in seconds.
        end_sec (int): The end time in seconds.
    
    Returns:
        AudioSegment: The trimmed audio segment.
    """
    # Load the audio file
    audio = AudioSegment.from_mp3(file_path)
    
    # Convert seconds to milliseconds for pydub
    start_ms = start_sec * 1000
    end_ms = end_sec * 1000
    
    # Ensure the end time does not exceed the audio length
    if end_ms > len(audio):
        end_ms = len(audio)
    
    # Trim the audio segment
    trimmed_audio = audio[start_ms:end_ms]
    
    return trimmed_audio

def combine_mp3(files, start_end_times, output_path):
    """
    Combines multiple MP3 files after editing them based on start and end times.
    Args:
        files (list of str): List of file paths to the MP3 files.
        start_end_times (list of tuples): List of tuples with start and end times (in seconds) for each file.
        output_path (str): The path for the output MP3 file.
    """
    combined_audio = AudioSegment.empty()
    
    for file, (start_sec, end_sec) in zip(files, start_end_times):
        edited_audio = edit_mp3(file, start_sec, end_sec)
        edited_audio = edited_audio.fade_in(1500)
        edited_audio = edited_audio.fade_out(1500)
        combined_audio += edited_audio
    
    combined_audio.export(output_path, format="mp3")
    print(f"Combined MP3 saved to {output_path}")

file1 = "songs/Siraima Sirbandi - New Nepali Movie _How Funny_ Song __ Priyanka Karki __ Melina Rai.mp3"
file2 = "songs/SURKE THAILI KHAI By Rajan Raj Shiwakoti _ Woda Number 6 _ Ft. Deepak Raj_Dipa Shree_ Priyanka.mp3"
file3 = "songs/Malai Maitai Sukha Chha - Nepali Movie BISH Song __ Rajesh Hamal, Sanchita Luitel __ Mandabi.mp3"
file4 = "songs/TeejKo Rahar (Re-Make) _ Manju Thapa Ft. Karishma Manandhar _ Nepali Superhit Teej Song.mp3"

files = [file1, file2, file3, file4]  
start_end_times = [(33, 64), (48, 70.5), (193, 246), (28, 93)]  

output_path = "combined_songs/combinedsong.mp3"  

combine_mp3(files, start_end_times, output_path)

#azusa
#Shorten the videos
ffmpeg -i computerworld.mp4 -ss 00:02 -to 00:46 -c:v copy -c:a copy azusa_computerworld.mp4
ffmpeg -i computerworld.mp3 -ss 00:11 -to 00:51 -c:v copy -c:a copy computerworld4.mp3
ffmpeg -i computerworld.mp3 -ss 00:11 -to 00:51 -c:v copy -c:a copy computerworld4.mp3

ffmpeg -i history.mp4 -ss 19:39 -to 19:50 -c:v copy -c:a copy history1.mp4
ffmpeg -i history.mp4 -ss 04:29 -to 04:36 -c:v copy -c:a copy history2.mp4
ffmpeg -i history.mp4 -ss 40:30 -to 40:37 -c:v copy -c:a copy history3.mp4
ffmpeg -i history.mp4 -ss 43:30 -to 43:37 -c:v copy -c:a copy history4.mp4
ffmpeg -i history.mp4 -ss 44:30 -to 44:37 -c:v copy -c:a copy history5.mp4

ffmpeg -i art1.mp4 -ss 06:13 -to 06:24 -c:v copy -c:a copy back1.mp4
ffmpeg -i art1.mp4 -ss 03:17 -to 03:24 -c:v copy -c:a copy back2.mp4
ffmpeg -i art1.mp4 -ss 05:15 -to 05:22 -c:v copy -c:a copy back3.mp4
ffmpeg -i art1.mp4 -ss 05:34 -to 05:41 -c:v copy -c:a copy back4.mp4
ffmpeg -i art1.mp4 -ss 04:03 -to 04:10 -c:v copy -c:a copy back6.mp4
ffmpeg -i art1.mp4 -ss 01:30 -to 01:38 -c:v copy -c:a copy back5.mp4

#Concatenate 
ffmpeg -i first.mp4 -i history4.mp4 -i history5.mp4 \
  -filter_complex "[0:v] [0:a] [1:v] [1:a] [2:v] [2:a] concat=n=3:v=1:a=1 [v] [a]" \
  -map "[v]" -map "[a]" first2.mp4

ffmpeg -i background1.mp4 -i back4.mp4 -i back2.mp4 \
  -filter_complex "[0:v] [0:a] [1:v] [1:a] [2:v] [2:a] concat=n=3:v=1:a=1 [v] [a]" \
  -map "[v]" -map "[a]" background3.mp4

#Concatenate with txt file
ffmpeg -f concat -safe 0 -i mylist2.txt -c copy concat_output.mov

#Overlayed Two Videos
ffmpeg \
-i computerworld_video.mp4 -i background3.mp4 \
-filter_complex " \
[0:v]setpts=PTS-STARTPTS, scale=480x360[top]; \
[1:v]setpts=PTS-STARTPTS, scale=480x360, \
format=yuva420p, colorchannelmixer=aa=0.5[bottom]; \
[top][bottom]overlay=shortest=1" \
-vcodec libx264 finalvideo2.mp4

#Fade out the audio of my videos
ffmpeg -i azusa_final.mp4 -af afade=t=in:st=0:d=3,afade=t=out:st=35:d=5 azusa_final_fade.mp4

#Code I tried out but didnot use for final video
ffmpeg -i 'space-%03d.png' -c:v libx264 -pix_fmt yuv420p space_q.mp4
ffmpeg -i 'vr-%03d.png' -c:v libx264 -pix_fmt yuv420p vr_q.mp4
ffmpeg  -i vr.mp4 -vf fps=1 vr-%03d.png
ffmpeg -i hands.mp4 -vf vflip -c:a copy hands_flip.mp4 
ffmpeg -i hands.mp4 -vf hflip -c:a copy hands_hflip.mp4 

ffmpeg -i vr_shorter.mp4  \
  -i vr_flip.mp4 \
  -filter_complex "color=white,[0:v:0]pad=iw*2:ih[bg]; [bg][1:v:0]overlay=w" \
  vrgirl.mp4

#sai
#check information
ffprobe -i 1_f.mp4 -show_format -v quiet

#transfer gif to MP4
ffmpeg -i 1.gif -vf scale=480:-2,format=yuv420p 1.mp4

#cut audio
ffmpeg -i robots.mp3 -ss 00:01:15 -t 00:00:40 -acodec copy bgm.mp3 

#add blur effect and set all videos into same frame size
ffmpeg -i 1.mp4 -lavfi "color=color=black@.5:size=480x270:d=1[dark]; [0:v]crop=480:270[blurbase]; [blurbase]boxblur=luma_radius='min(h,w)/20':luma_power=1:chroma_radius='min(cw,ch)/20':chroma_power=1[blurred]; [blurred][dark]overlay[darkened]; [darkened]scale=480:360[bg]; [0:v]scale=-1:360[fg]; [bg][fg]overlay=(W-w)/2:(H-h)/2" 1_blur.mp4  

#cut video
ffmpeg -ss 00:00:00 -t 00:00:01.24 -i 2.mp4 -c:v libx264 -preset superfast -c:a copy 2_f.mp4

# change frame rate
ffmpeg -i input.mov -qscale 0 -r 25 -y output.mov 

# change volume
ffmpeg -i input.wav -af volume=+3dB output.wav

#change speed of video
ffmpeg -i 1.mp4 -vframes 50 1_f.mp4

#combine video and audio
ffmpeg -y -i output.mp4 -i bgm.mp3 -c:v copy -c:a aac -strict experimental -map 0:v:0 -map 1:a:0 sailiu.mp4  
 
#concatenating media files
ffmpeg -y -f concat -safe 0 -i mylist.txt -c copy output.mp4  

#audio fade
ffmpeg -i 1.mp4 -af afade=t=in:st=0:d=3,afade=t=out:st=35:d=5 1_fade.mp4 

#wayne
#Extract the audio from the song
ffmpeg -i music.mp3 -ss 00:00:00 -to 00:00:10 -acodec copy music1.mp3
ffmpeg -i music.mp3 -ss 00:01:29 -to 00:01:52 -acodec copy music2.mp3
ffmpeg -i music.mp3 -ss 00:02:03 -to 00:02:13 -acodec copy music3.mp3

#Combine the song
nano musicls.txt
file 'music1.mp3'
file 'music2.mp3'
file 'music3.mp3'

ffmpeg -f concat -i musicls.txt -c copy m_output.mp3

#Trans the format from the gif to mp4
ffmpeg -i giphy1.gif -vf scale=420:-2,format=yuv420p animation1.mp4

#Combine the audio and the video
ffmpeg -f concat -i video.txt -c copy output.mp4

#Change the velocity of the video
ffmpeg -i output.mp4 -r 16 -filter:v "setpts=0.75*PTS" output_v.mp4

#Combine the audio and the video
ffmpeg -i output.mp4 -i m_output.mp3 -map 0:v -map 1:a -c copy -shortest outputfinal.mp4

#Delate the audio from the video (-an)
ffmpeg -i outputfinal.mp4 -c copy -an outputfinal_nosound.mkv

#Change the video's frame rate and the scale
ffmpeg -i input.mov -qscale 0 -r 25 -y output.mov 
ffmpeg -i outputp2.mp4 -vf scale=480:360 video_480.mp4 -hide_banner

#fade in/out the video
ffmpeg -i output.mp4 -af afade=t=in:st=0:d=3,afade=t=out:st=35:d=5 output_fade.mp4

#Combine the audio and the video
ffmpeg -i output_nosound.mp4 -i m_output.mp3 -c:v copy -c:a aac -strict experimental Wayne_outputfinal.mp4
import "@egjs/view360/css/view360.min.css";
import { useEffect, useRef, useState } from "react";
import View360, { EquirectProjection, ControlBar } from "@egjs/react-view360";
import Hls from "hls.js";

const VideoPage = () => {
  const url = "https://test-streams.mux.dev/x36xhzz/x36xhzz.m3u8";
  const demoUrl="https://pchen66.github.io/Panolens/examples/asset/textures/video/ClashofClans.mp4"
const isHls = false;
  const videoRef = useRef(null);
  const [projection, setProjection] = useState(null);

  console.log('videoRef', videoRef);
  console.log('Hls.isSupported()', Hls.isSupported());

  const controlBar = new ControlBar({
    autoHide: true,
    autoHideTimeout: 1000,
    autoHideTime: 1000,
    easing: "ease",
    direction: "vertical",
    button: {
      fullscreen: true,
      vr: true,
      gyro: true,
      play: true,
      pause: true,
      volume: true,
      mute: true,
      zoom: true,
      setting: true,
    },
  });

  useEffect(() => {
    if (videoRef.current) {
      console.log("Video element loaded:", videoRef.current);
      if (Hls.isSupported() && isHls) {
        const hls = new Hls();
        hls.loadSource(url);
        hls.attachMedia(videoRef.current);
        console.log("HLS Player created:", hls);

        hls.on(Hls.Events.MANIFEST_PARSED, () => {
          console.log("HLS Manifest parsed, vidd");
          videoRef.current.play();
        });

        hls.on(Hls.Events.ERROR, (event, data) => {
          console.error("HLS error:", data);
        });
      } else if (videoRef.current.canPlayType("application/vnd.apple.mpegurl")) {
        videoRef.current.src = demoUrl;
        videoRef.current.addEventListener('loadedmetadata', () => {
          console.log("Video metadata loaded, video can be played");
          videoRef.current.play();
        });
        
      } else{
        console.log("Video can't be played");
        videoRef.current.src = demoUrl;
        videoRef.current.addEventListener('loadedmetadata', () => {
          console.log("Video metadata loaded, video can be played");
          videoRef.current.play();
        });
      }

      // Create EquirectProjection after video has loaded
      const newProjection = new EquirectProjection({
        src: videoRef.current,
        video: {
          autoplay: false,
          muted: true,

        },
        zoom: false,
      });
      console.log("EquirectProjection created:", newProjection);
      setProjection(newProjection);
    }
  }, [videoRef.current]); // This will re-run only when videoRef is set

  return (
    <div className="h-full w-full">
      <video
        ref={videoRef}
        controls
        autoPlay
        playsInline
        muted
        crossOrigin="anonymous"
        style={{ width: "100%", height: "auto", display: "none" }}
      >
      
        Your browser does not support the video tag.
      </video>

      {projection && (
        <View360
          className="is-16by9"
          projection={projection}
          autoplay={false}
          plugins={[controlBar]}
          zoom={true}
      
        />
      )}
    </div>
  );
};

export default VideoPage;
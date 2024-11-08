import { VideoCard } from '../components/VideoCard.jsx';

const videos = [
  {
    thumbnail: 'https://img.daisyui.com/images/stock/photo-1606107557195-0e29a4b5b4aa.webp',
    title: 'Shoes!',
    channel: 'Shoe Store',
    views: 1000,
  },
  {
    thumbnail: 'https://img.daisyui.com/images/stock/photo-1606107557195-0e29a4b5b4aa.webp',
    title: 'Shoes!',
    channel: 'Shoe Store',
    views: 1000,
  },
  {
    thumbnail: 'https://img.daisyui.com/images/stock/photo-1606107557195-0e29a4b5b4aa.webp',
    title: 'Shoes!',
    channel: 'Shoe Store',
    views: 1000,
  },
  {
    thumbnail: 'https://img.daisyui.com/images/stock/photo-1606107557195-0e29a4b5b4aa.webp',
    title: 'Shoes!',
    channel: 'Shoe Store',
    views: 1000,
  }
]

export const Home = () => {
  return (
    <>
      <div>
        <h1 className="text-5xl font-extrabold   mt-10  text-left">Introducing Project 360</h1>
        <p className=" text-left text-xl mt-6">
          Project 360 is revolutionizing 360° surveillance for drones and security, advancing beyond the limitations of traditional camera systems to deliver full-spectrum awareness and AI-ready tracking capabilities.
        </p>

        <div className="grid grid-cols-1 md:grid-cols-2 gap-8 mt-10 pb-16">
          <div>
            <h2 className="text-2xl font-semibold mb-4 text-left">Traditional Camera Systems</h2>
            <ul className="text-lg list-disc list-inside ml-4 space-y-2">
              <li>Limited field of view, requiring multiple cameras to cover large areas</li>
              <li>Fixed perspectives, reducing adaptability to moving targets</li>
              <li>Manual monitoring or limited automation for tracking</li>
              <li>Increased setup complexity with multiple devices and wiring</li>
            </ul>
          </div>

          <div>
            <h2 className="text-2xl font-semibold mb-4 text-left">Project 360 System</h2>
            <ul className="text-lg list-disc list-inside ml-4 space-y-2">
              <li>Seamless 360° coverage with fewer devices</li>
              <li>Dynamic tracking enabled by AI, adapting to movement in real time</li>
              <li>Comprehensive awareness that enhances automated surveillance</li>
              <li>Streamlined setup with fewer devices, minimizing complexity</li>
            </ul>
          </div>
        </div>



      </div>
<div className='text-left pb-10'>
        <h2 className="text-3xl font-extrabold  mt-10 text-left">Featured Videos</h2>
        <p className=" text-left text-lg mt-6">
          Watch the latest videos from Project 360 to see our system in action and learn how it can enhance your surveillance capabilities.
        </p>
</div>

      <div className="grid grid-cols-1 lg:grid-cols-3 md:grid-cols-2 gap-14 "  >
        {videos.map((video, index) => (
          <VideoCard key={index} video={video} />
        ))}
      </div>
    </>
  );
};

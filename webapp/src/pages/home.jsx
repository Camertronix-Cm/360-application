import { VideoCard } from '../components/VideoCard.jsx';

export const Home = () => {
  return (
    <div className="grid gap-4" style={{ gridTemplateColumns: 'repeat(auto-fit, minmax(250px, 1fr))' }}>
      <VideoCard
        video={{
          thumbnail: 'https://img.daisyui.com/images/stock/photo-1606107557195-0e29a4b5b4aa.webp',
          title: 'Shoes!',
          channel: 'Shoe Store',
          views: 1000,
        }}
      />
      <VideoCard
        video={{
          thumbnail: 'https://img.daisyui.com/images/stock/photo-1606107557195-0e29a4b5b4aa.webp',
          title: 'Shoes!',
          channel: 'Shoe Store',
          views: 1000,
        }}
      />
      <VideoCard
        video={{
          thumbnail: 'https://img.daisyui.com/images/stock/photo-1606107557195-0e29a4b5b4aa.webp',
          title: 'Shoes!',
          channel: 'Shoe Store',
          views: 1000,
        }}
      />
      <VideoCard
        video={{
          thumbnail: 'https://img.daisyui.com/images/stock/photo-1606107557195-0e29a4b5b4aa.webp',
          title: 'Shoes!',
          channel: 'Shoe Store',
          views: 1000,
        }}
      />
    </div>
  );
};

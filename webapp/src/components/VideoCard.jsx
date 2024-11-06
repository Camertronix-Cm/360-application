import PropTypes from 'prop-types';

export const VideoCard = ({ video }) => {

    VideoCard.propTypes = {
        video: PropTypes.shape({
            thumbnail: PropTypes.string.isRequired,
            title: PropTypes.string.isRequired,
            channel: PropTypes.string.isRequired,
            views: PropTypes.number.isRequired,
        }).isRequired,
    };
    return (
        <div className="video-card">
            <img src={video.thumbnail} alt={video.title} />
            <div className="video-card-info">
                <h3>{video.title}</h3>
                <p>{video.channel}</p>
                <p>{video.views} views</p>
            </div>

            <div className="card bg-base-100 w-96 shadow-xl">
                <figure>
                    <img
                        src="https://img.daisyui.com/images/stock/photo-1606107557195-0e29a4b5b4aa.webp"
                        alt="Shoes" />
                </figure>
                <div className="card-body">
                    <h2 className="card-title">Shoes!</h2>
                    <p>If a dog chews shoes whose shoes does he choose?</p>
                    <div className="card-actions justify-end">
                        <button className="btn btn-primary">Buy Now</button>
                    </div>
                </div>
            </div>
        </div>
    );



}
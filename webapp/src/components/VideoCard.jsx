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
          

            <div className="card bg-base-100 w-96 shadow-xl">
                <figure>
                    <img
                        src={video.thumbnail}
                        alt="Shoes" />
                </figure>
                <div className="card-body">
                    <h2 className="card-title">{video.title}</h2>
                    <p>If a dog chews shoes whose shoes does he choose?</p>
                    <div className="card-actions justify-end">
                        <button className="btn btn-primary">Buy Now</button>
                    </div>
                </div>
            </div>
        </div>
    );



}
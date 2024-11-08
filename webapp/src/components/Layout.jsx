import PropTypes from 'prop-types';
import Header from './Header';
import Footer from './Footer';

export const Layout = ({ children }) => {
    return (
        <div className="container mx-auto px-5 flex flex-col min-h-screen">
            <div className="w-full">
                <Header />
            </div>
            <main className="w-full flex-grow">
                <div className="w-full">
                    {children}
                </div>
            </main>
            <Footer />
        </div>
    );
};

Layout.propTypes = {
    children: PropTypes.node.isRequired,
};
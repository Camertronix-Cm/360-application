

import PropTypes from 'prop-types';
import Header from './Header';
import Footer from './Footer';


export const Layout = ({ children }) => {
 

return (
    <div className='container mx-auto px-4 '>
    <Header />

      {children}

    <Footer />
    </div>
  );
  
}
Layout.propTypes = {
    children: PropTypes.node.isRequired,
};




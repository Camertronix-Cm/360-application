 
import PropTypes from 'prop-types';

const Layout = ({ children }) => {
    return (
        <div className="layout">
            <header>
                <h1>My Application</h1>
            </header>
            <main>
                {children}
            </main>
            <footer>
                <p>&copy; 2023 My Application</p>
            </footer>
        </div>
    );
};
Layout.propTypes = {
    children: PropTypes.node.isRequired,
};
 
export default Layout;